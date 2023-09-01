#include <iostream>
#include <fstream>

#include <array>
#include <vector>
#include <string>

#include <algorithm>

class CPoint {

    public:

        //Constructors
        CPoint()
        {
            std::cout<<"CPoint::CPoint()\n";
        }

        CPoint(double x, double y, double z)
        {
            std::cout<<"CPoint::CPoint(double x, double y, double z)\n";
            SetCoord(x,y,z);
        }

        CPoint(const CPoint& P)
        {
            std::cout<<"CPoint::CPoint(const CPoint& P)\n";
            coord=P.coord;
        }

        //Destructors
        ~CPoint()
        {
            std::cout<<"CPoint::~CPoint()\n";
        }

        //Overloading Operators
        CPoint& operator=(const CPoint& P)
        {
            //assignement oerator
            std::cout<<"CPoint::operator=(const CPoint& P)\n";
	    coord=P.coord;
            return *this;
        }

        bool operator==(const CPoint& P) const
        {
	    std::cout<<"CPoints::operator==(const CPoint& P)\n";
            return coord==P.coord;
        }

        //Setters (list function pointers for general dimension)
        void SetCoord(double x, double y, double z)
        {
            std::cout<<"CPoint::SetCoord(double x, double y, double z)\n";
            coord={x,y,z};
        }

        void SetX(double x)
        {
            std::cout<<"CPoint::SetX(double x)\n";
            coord[0]=x;
        }

        void SetY(double y)
        {
            std::cout<<"CPoint::SetY(double y)\n";
            coord[0]=y;
        }

        void SetZ(double z)
        {
            std::cout<<"CPoint::SetZ(double z)\n";
            coord[0]=z;
        }

        //Getters
        std::array<double,3> GetCoord()
        {
            std::cout<<"CPoint::GetCoord()\n";
            return coord;
        }

        auto GetX()
        {
            std::cout<<"CPoint::GetX()\n";
            return coord[0];
        }

        auto GetY()
        {
            std::cout<<"CPoint::GetY()\n";
            return coord[1];
        }

        auto GetZ()
        {
            std::cout<<"CPoint::GetZ()\n";
            return coord[2];
        }

	/////////////////////////////////////////////////////
	
	virtual void print()
	{
	    std::cout<<"CPoints::print()\n";
	    std::cout<<'['<<coord[0]<<','<<coord[1]<<','<<coord[2]<<"]\n";
	}
	

    protected:
        // default init to 0s -> default constructor with no arguments works
	std::array<double,3> coord = {0., 0., 0.};


};

class CMassPoint : public CPoint {

    public:
	CMassPoint()
	{
	    std::cout<<"CMassPoint::CMassPoint()\n";
	};
	
	CMassPoint(double x, double y, double z, double m)
	{
	    std::cout<<"CMassPoint::CMassPoint(double x, double y, double z, double m)\n";
	    mass=m;
	    SetCoord(x,y,z);
	}

	~CMassPoint()
	{
	    std::cout<<"CMassPoint::~CMassPoint()\n";
	}


        CMassPoint(const CMassPoint& P) : CPoint(P)
        {
            std::cout<<"CMassPoint::CMassPoint(const CPoint& P)\n";
            mass=P.mass;
        }

        bool operator==(const CMassPoint& P) const
        {
	    std::cout<<"CMassPoints::operator==(const CMassPoint& P)\n"; 
            return coord==P.coord && mass==P.mass;
        }

	void SetM(double m)
	{
	    std::cout<<"CMassPoint::SetM(double m)\n";
	    mass=m;
	}

	double GetM()
	{
	    std::cout<<"CMassPoint::GetM()\n";
	    return mass;
	}

	virtual void print()
	{
	    std::cout<<"CMassPoint::print()\n";
	    double x=GetX();
	    double y=GetY();
	    double z=GetZ();
	    std::cout<<'['<<x<<','<<y<<','<<z<<';'<<mass<<"]\n";
	}

    protected:
	double mass=1.;

};


class CMassPointSystem {

    public:
	std::vector<CMassPoint> points;

	CMassPointSystem(){}

	void addMassPoint(CMassPoint mp)
	{
	    points.push_back(mp);
	}

	void removeMassPoint(int index)
	{
	    points.erase(points.begin()+index);
	}

	void print()
	{
	    //std::cout<<"Points in system:\n";

	    for(auto& P : points)
		P.print();
	}

	bool operator==(CMassPointSystem Sys) 
	{
	    //Sys è locale, devo eliminare elementi
	    if(points.size()!=Sys.points.size()) return false;

	    for(int i=0; i<points.size(); i++)
	    {
		auto el = std::find(Sys.points.begin(), Sys.points.end(), points[i]); 

	        if(el == Sys.points.end()) return false;

		Sys.points.erase(el);
	    }

	    return true; // basta return true, è per forza vuoto se arriva qui

	}

	void barycenter()
	{
	    double Xc=0.,Yc=0., Zc=0., M=0.;

	    for(auto& P: points)
	    {
	        M+=P.GetM();
		Xc+=P.GetX()*P.GetM();
		Yc+=P.GetY()*P.GetM();
		Zc+=P.GetZ()*P.GetM();
	    }

	    if(M==0) std::cout<<"Error, M=0\n";
	    Xc/=M;
	    Yc/=M;
	    Zc/=M;
	
	    std::cout<<"Baricentro: X="<<Xc<<" Y="<<Yc<<" Z="<<Zc<<"\n";
	}

	void save(std::string filename)
	{
	    std::ofstream file(filename);

	    if (!file)
       	    {
	    std::cerr << "error opening the file!\n";
	    std::exit(1);
	    }
	
	    for(auto& P : points)
	        file<<P.GetX()<<"\t"<<P.GetY()<<"\t"<<P.GetZ()<<"\t"<<P.GetM()<<"\n";
	    
	}

};


int main()
{

	std::cout << "\n\nCPoint test\n\n";
	CPoint p1, p2(10, 20, 30), p3, p4(p2); // static definition
	p3 = p2;
	p1.print(); // prints out: [0, 0, 0]
	p2.print(); // prints out: [10, 20, 30]
	p3.print(); // prints out: [10, 20, 30]
	p4.print(); // prints out: [10, 20, 30]
	p4.SetX(20);
	p4.print(); // prints out: [20, 20, 30]	std::cin.ignore();

	std::cout<<"----------------------------------------------------\n";

	std::cout << "\n\nCMassPoint test\n\n";

	CMassPoint mp1, mp2(10, 20, 30, 100), mp3, mp4(mp2); // static definition
	mp3 = mp2;
	mp1.print(); // prints out: [0, 0, 0; 1]
	mp2.print(); // prints out: [10, 20, 30; 100]
	mp3.print(); // prints out: [10, 20, 30; 100]
	mp4.print(); // prints out: [10, 20, 30; 100]
	mp4.SetX(20);
	mp4.SetM(55);
	mp4.print(); // prints out: [20, 20, 30; 55]
	std::cout << "Dynamic definition\n";
	CMassPoint *pCMP = new CMassPoint;
	pCMP->print(); // prints out: [0, 0, 0; 1]
	delete pCMP;
	std::cout << "A pointer to CMassPoint\n";
	pCMP = &mp4;
	pCMP->print(); // prints out: [20, 20, 30, 55]
	std::cout << (*pCMP == mp4) << "\n"; // prints out: 1
	std::cout << "A pointer to CPoint, pointing to a CMassPoint\n";
	CPoint *pCP = &mp1; // pointer to CPoint, pointing to mp1, a CMassPoint
	pCP -> print(); // MUST print out: [0, 0, 0; 1]!!!!!! (virtual in both base and derived) 
			// https://stackoverflow.com/questions/18885224/how-to-call-derived-class-method-from-base-class-pointer)
	std::cout << (*pCP == mp1) << "\n"; // what does this print out?
	std::cout << "CMassPoint test: mp2 and mp3 are equal, let us verify\n";
	if (mp2 == mp3)
	std::cout << "Yes, they are\n";
	else
	std::cout << "No, they are not\n";

	std::cout<<"----------------------------------------------------\n";


	std::cout << "\n\nCMassPointSystem test\n\n";
	CMassPointSystem s;
	s.addMassPoint(mp1);
	s.addMassPoint(mp3);
	s.addMassPoint(mp1);
	std::cout << "Checking s content\n";
	s.print();
	s.removeMassPoint(0);
	std::cout << "Checking s content again\n";
	s.print();
	std::cout << "CMassPointSystem test2\n";
	CMassPointSystem s2;
	s2.addMassPoint(mp1);
	s2.addMassPoint(mp3);
	std::cout << "Checking if s and s2 are equal\n";
	if (s == s2)
	std::cout << "Yes, they are\n";
	else
	std::cout << "No, they are not\n";

	std::cout<<"----------------------------------------------------\n";
	s.barycenter();
	s.save("output.txt");


	return 0;

}
