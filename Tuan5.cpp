#include<conio.h>
#include<cstring>
#include<sstream>  
#include<windows.h>
#include<iomanip>  //setw()
#include<fstream>   //thu vien cua file
#include<iostream>
#include<algorithm> //thu vien doi tat ca thnah chu hoa
using namespace std;
//
void gotoxy(int x,int y){
	static HANDLE h=NULL;
	if(!h)
		h = GetStdHandle(STD_OUTPUT_HANDLE);
		COORD c={x,y};
		SetConsoleCursorPosition(h,c);
}
//
struct hoVaTen{
	string ten;
	string ho;
};
struct ngaySinh{
	int ngay,thang,nam;
};
struct sinhVien{
	string maLop;
	string maSV;
	hoVaTen Ten;
	ngaySinh Date;
	float DTBTL;
};
typedef struct Node{
	struct Node *pNext;
	sinhVien data;
}NODE;

struct List{
	NODE *pHead;
	NODE *pTail;
};

void init(List &l){
	l.pHead = l.pTail = NULL;
}

NODE *GetNode(sinhVien DATA){
	NODE *p = new NODE;
	if(p==NULL) return NULL;	
	p->data = DATA;
	p->pNext =  NULL;
	return p;
}

void addTail(List &l,NODE *p){
	if(l.pHead == NULL){
		l.pHead = l.pTail = p;
	}else{
		l.pTail->pNext = p;
		l.pTail = p;
	}
}
// Thong Ke ----------------

struct thongKe{
	string Lop;
	int soSV;
	int sl_XS,sl_Gioi,sl_Kha,sl_TB,sl_Yeu;
	float tle_XS,tle_G,tle_K,tle_TB,tle_Y;
};

int kiemTra_Diem(float DTBTL){
	if(DTBTL<0 or DTBTL>4) return 0;
	else return 1;
}

int kiemTra_Date(sinhVien p){
	if(p.Date.thang<1 or p.Date.thang>12 or p.Date.nam<1900 or p.Date.nam >2016) return 0;
	else{
		switch(p.Date.thang){
			case 1: case 3: case 5: case 7: case 8: case 10: case 12:{
				if(p.Date.ngay<0 or p.Date.ngay>31)	return 0;
				else return 1;
				break;
			}
			case 4: case 6: case 9: case 11:{
				if(p.Date.ngay<1 or p.Date.ngay>30) return 0;
				else return 1;
				break;
			}
			case 2:{
				if(p.Date.ngay<0 or(p.Date.nam%4==0 and p.Date.ngay>29)or(p.Date.nam%4!=0 and p.Date.ngay>28))return 0;
				else return 1;
				break;
			}
		}
	}
}

int kiemTra_maSV(sinhVien p){
	if(p.maSV.length() !=8) return 0;     
	else return 1;
}
//Xoa khoang trang dau va cuoi chuoi
void xoa(string &str){
	while(str[0]==' '){
		str.erase(str.begin() + 0);  // Ham xoa Vi tri 0
	}
	while(str[str.length() - 1]==' '){
		str.erase(str.begin() + str.length()-1);  //Xoa cuoi
	}
}

void xoaGiua(string &str){
	for(int i=0;i<str.length()-1;i++){
		if(str[i]==' ' and str[i+1]==' '){
			str.erase(str.begin() + i);
			i--; 
		}
	}
}

void inHoa(string &str){
	std::transform(str.begin() ,str.end() ,str.begin(), ::tolower); //Chuyen tat ca thanh chu thuong
	str[0] = toupper(str[0]);
	for(int i=1;i<str.length();i++){
		if(str[i]==' '){
			str[i+1]=toupper(str[i+1]);
		}
	}
}

void write_File(sinhVien x){
	ofstream f;
	f.open("SinhVien.dat",ios::binary|ios::out|ios::app);
	f<<" "<<x.Ten.ho<<","<<x.Ten.ten<<","<<x.maLop<<","<<x.maSV<<","<<x.Date.ngay<<" "<<x.Date.thang<<" "<<x.Date.nam<<" "<<x.DTBTL;
	f.close();
}
//
void khung(){
	HANDLE h;
	h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h,15);
	cout<<endl;
	cout<<"	+-----------------------------------------------------------------+"<<endl;
	cout<<"	| Ho va Ten dem |                                                 |"<<endl;
	cout<<"	|-----------------------------------------------------------------|"<<endl;
	cout<<"	| Ten           |                                                 |"<<endl;
	cout<<"	|-----------------------------------------------------------------|"<<endl;
	cout<<"	| Ma Lop        |                                                 |"<<endl;
	cout<<"	|-----------------------------------------------------------------|"<<endl;
	cout<<"	| Ma SV         |                                                 |"<<endl;
	cout<<"	|-----------------------------------------------------------------|"<<endl;
	cout<<"	| Ngay sinh     |                                                 |"<<endl;
	cout<<"	|-----------------------------------------------------------------|"<<endl;
	cout<<"	| DTBTL         |                                                 |"<<endl;
	cout<<"	+-----------------------------------------------------------------+"<<endl;
}
//
void themHoSo(){
	HANDLE h;
	h = GetStdHandle(STD_OUTPUT_HANDLE);
	int n;
	cout<<" 	  [?] Ban muon nhap bao nhieu sinh vien : "; cin>>n;
	for(int i=1;i<=n;i++){
		system("cls");
		sinhVien x;
		cin.ignore();   // thêm vào d? xoá b? nh? d?m, tránh b? trôi l?nh
		cout<<"\n => Nhap thong tin thu "<<i<<" :"<<endl;
		khung();		
//		
		SetConsoleTextAttribute(h,11); gotoxy(10,4); cout<<"Ho va Ten dem"; SetConsoleTextAttribute(h,15);
		gotoxy(26,4); getline(cin,x.Ten.ho);
		xoa(x.Ten.ho); xoaGiua(x.Ten.ho); inHoa(x.Ten.ho);
		gotoxy(26,4); cout<<"                                           "; 
		gotoxy(26,4); cout<<x.Ten.ho;
//		
		SetConsoleTextAttribute(h,11); gotoxy(10,6); cout<<"Ten"; SetConsoleTextAttribute(h,15);		
		gotoxy(26,6); getline(cin,x.Ten.ten);
		xoa(x.Ten.ten);	xoaGiua(x.Ten.ten); inHoa(x.Ten.ten);
		gotoxy(26,6); cout<<"                                         ";
		gotoxy(26,6); cout<<x.Ten.ten;
//		
		SetConsoleTextAttribute(h,11); gotoxy(10,8); cout<<"Ma Lop"; SetConsoleTextAttribute(h,15);	
		gotoxy(26,8);  cin>>x.maLop;
		std::transform(x.maLop.begin(),x.maLop.end(),x.maLop.begin(), ::toupper); 
		gotoxy(26,8); cout<<"                                 ";
		gotoxy(26,8); cout<<x.maLop;
//		
		do{
			SetConsoleTextAttribute(h,11); gotoxy(10,10); cout<<"Ma SV"; SetConsoleTextAttribute(h,15);
			gotoxy(26,10);
			cout<<"                                    ";
			gotoxy(26,10);
			cin>>x.maSV;
			kiemTra_maSV(x);
		}while(kiemTra_maSV(x)==0);
//		
		do{
			SetConsoleTextAttribute(h,11); gotoxy(10,12); cout<<"Ngay sinh"; SetConsoleTextAttribute(h,15);
			gotoxy(26,12); 
			cout<<"                                      ";
			gotoxy(26,12); cin>>x.Date.ngay>>x.Date.thang>>x.Date.nam;
			kiemTra_Date(x);
			gotoxy(26,12); cout<<x.Date.ngay<<"/"<<x.Date.thang<<"/"<<x.Date.nam;
		}while(kiemTra_Date(x)==0);
//
		do{
			SetConsoleTextAttribute(h,11); gotoxy(10,14); cout<<"DTBTL"; SetConsoleTextAttribute(h,15);
			gotoxy(26,14); 
			cout<<"                                       ";
			gotoxy(26,14);
			cin>>x.DTBTL;
			kiemTra_Diem(x.DTBTL); 
		}while(kiemTra_Diem(x.DTBTL)==0);
//		
		write_File(x);
	}
}
// Doc file
void readFile(List &l){
	init(l);
	ifstream f;
	f.open("SinhVien.dat",ios::in);
	if(f==NULL)  cout<<"Chua co du lieu...."<<endl;
	else{
		while(!f.eof()){
			sinhVien p;
			getline(f,p.Ten.ho,',');
			getline(f,p.Ten.ten,',');
			getline(f,p.maLop,',');
			getline(f,p.maSV,',');
			f>>p.Date.ngay;
			f>>p.Date.thang;
			f>>p.Date.nam;
			f>>p.DTBTL;
			//
			NODE *t = GetNode(p);
			addTail(l,t);
		}
	}
	f.close();
}
// In danh sach
void inDanhSach(List &l){
	readFile(l);
	int y=8,t=1;
	NODE *p = l.pHead;
	cout<<endl;
	cout<<"		+______________________________________DANH SACH SINH VIEN________________________________________+"<<endl;
	cout<<"		|                                                                                                 |"<<endl;
	cout<<"		| STT |        HO  VA  TEN            |    MA  LOP    |    MA  SV    |    NGAY  SINH    |  DTBTL  |"<<endl;
	cout<<"		|-----|-------------------------------|---------------|--------------|------------------|---------|";
	while(p!=NULL){
		gotoxy(16,y); cout<<"| "<<t;
		gotoxy(22,y); cout<<"|    "<<p->data.Ten.ho<<" "<<p->data.Ten.ten;
		gotoxy(54,y); cout<<"|   "<<p->data.maLop;
		gotoxy(70,y); cout<<"|   "<<p->data.maSV;
		gotoxy(85,y); cout<<"|    "<<p->data.Date.ngay<<"/"<<p->data.Date.thang<<"/"<<p->data.Date.nam;
		gotoxy(104,y); cout<<"|  "<<p->data.DTBTL<<setprecision(2)<<fixed;
		gotoxy(114,y); cout<<"|"<<endl;
		cout<<"		|-----|-------------------------------|---------------|--------------|------------------|---------|"<<endl;
		p=p->pNext;
		y+=2;
		t++;
	}
}
//
void in_sx(List &l){
	int y=6,t=1;
	NODE *p = l.pHead;
	cout<<endl;
	cout<<"		KET QUA SAP XEP:"<<endl;
	cout<<"		+_____________________________________DANH SACH SINH VIEN_________________________________________+"<<endl;
	cout<<"		|                                                                                                 |"<<endl;
	cout<<"		| STT |        HO  VA  TEN            |    MA  LOP    |    MA  SV    |    NGAY  SINH    |  DTBTL  |"<<endl;
	cout<<"		|-----|-------------------------------|---------------|--------------|------------------|---------|";
	while(p!=NULL){
		gotoxy(16,y); cout<<"| "<<t;
		gotoxy(22,y); cout<<"|    "<<p->data.Ten.ho<<" "<<p->data.Ten.ten;
		gotoxy(54,y); cout<<"|   "<<p->data.maLop;
		gotoxy(70,y); cout<<"|   "<<p->data.maSV;
		gotoxy(85,y); cout<<"|    "<<p->data.Date.ngay<<"/"<<p->data.Date.thang<<"/"<<p->data.Date.nam;
		gotoxy(104,y); cout<<"|  "<<p->data.DTBTL<<setprecision(2)<<fixed;
		gotoxy(114,y); cout<<"|"<<endl;
		cout<<"		|-----|-------------------------------|---------------|--------------|------------------|---------|"<<endl;
		p=p->pNext;
		y+=2;
		t++;
	}
}
// Hoan vi
void hoanVi(NODE *a,NODE *b){
	sinhVien x;
	x = a->data;
	a->data = b->data;
	b->data = x;
}
// 1.Sap xep Ngay sinh

//Sap xep Chon
void sx_NgaySinh_Chon(List &l){
	readFile(l);
	for(NODE *i=l.pHead ; i!=l.pTail; i=i->pNext){
		for(NODE *j=i->pNext ;j!=NULL ;j=j->pNext){
			if(i->data.Date.nam > j->data.Date.nam)  hoanVi(i,j);
			if(i->data.Date.nam == j->data.Date.nam){
				if(i->data.Date.thang > j->data.Date.thang)  hoanVi(i,j);
				if(i->data.Date.thang==j->data.Date.thang){
					if(i->data.Date.ngay > j->data.Date.ngay)  hoanVi(i,j);
				}
			}
		}
	}
	in_sx(l);
}
//Sap xep Chen
void sx_NgaySinh_Chen(List &l){
	readFile(l); 
	for(NODE *i=l.pHead;i!=l.pTail;i=i->pNext){
		NODE *k=i;
		for(NODE *j=i->pNext;j!=NULL;j=j->pNext){
			if(k->data.Date.nam > j->data.Date.nam)  k=j;
			if(k->data.Date.nam == j->data.Date.nam){
				if(k->data.Date.thang > j->data.Date.thang)  k=j;
				if(k->data.Date.thang == j->data.Date.thang){
					if(k->data.Date.ngay > j->data.Date.ngay)  k=j;
				}
			}
		}
		if(k!=i)  hoanVi(i,k);
	}
	in_sx(l);
}

// 2.Sap xep ma sinh vien

//Sap xep chon
void sx_MaSV_Chon(List &l){
	readFile(l);
	for(NODE *i=l.pHead ;i!=l.pTail ;i=i->pNext){
		for(NODE *j=i->pNext ;j!=NULL;j=j->pNext){
			if(i->data.maSV > j->data.maSV)  hoanVi(i,j);
		}
	}
	in_sx(l);
}
//Sap xep Chen
void sx_MaSV_Chen(List &l){
	readFile(l);
	for(NODE *i=l.pHead ;i!=l.pTail ;i=i->pNext){
		NODE *k = i;
		for(NODE *j=i->pNext ;j!=NULL ;j=j->pNext){
			if(k->data.maSV > j->data.maSV)  k = j;
		}
		if(k != i)  hoanVi(k,i);
	}
	in_sx(l);
}
// 3.Sap xep theo Ten

// Chon
void sx_Ten_Chon(List &l){
	readFile(l);
	for(NODE *i=l.pHead ;i!=l.pTail ;i=i->pNext){
		for(NODE *j=i->pNext ;j!=NULL ;j=j->pNext){
			if(i->data.Ten.ten == j->data.Ten.ten){
				string s1 = " ";
				string s2 = " ";
				string t1 = i->data.Ten.ho;
				string t2 = j->data.Ten.ho;
				std::size_t x1 = t1.find(s1);
				std::size_t x2 = t2.find(s2);
				if(t1.compare(x1+1,t1.length()-x1,t2,x2+1,t2.length()-x2) >0) hoanVi(i,j);
			}
			if(i->data.Ten.ten > j->data.Ten.ten)  hoanVi(i,j);
		}
	}
	in_sx(l);
}
// Chen
void sx_Ten_Chen(List &l){
	readFile(l);
	for(NODE *i=l.pHead;i!=l.pTail;i=i->pNext){
		NODE *k=i;
		for(NODE *j=i->pNext;j!=NULL;j=j->pNext){
			if(k->data.Ten.ten > j->data.Ten.ten)  k=j;
			if(k->data.Ten.ten == j->data.Ten.ten){
				string s1 = " ";
				string s2 = " ";
				string t1 = k->data.Ten.ho;
				string t2 = j->data.Ten.ho;
				std::size_t x1 = t1.find(s1);
				std::size_t x2 = t2.find(s2);
				if(t1.compare(x1+1,t1.length()-x1,t2,x2+1,t2.length()-x2) >0) k=j;
//				int n1=1 ,n2=1;
//				string s1=k->data.Ten.ho;
//				string s2=j->data.Ten.ho;
//				for(int m=1;m<s1.length();m++){
//					if(s1[n1]==' ')  break;
//					n1++;
//				}
//				for(int l=1;l<s2.length();l++){
//					if(s2[n2]==' ')  break;
//					n2++;
//				}
//				if(s1.compare(n1,s1.length()-n1,s2,n2,s2.length()-n2) >0)  k=j;	
			}
		}
		if(k!=i)  hoanVi(k,i);
	}
	in_sx(l);
}
// 4.Sap xep theo Ma lop

// Chon
void sx_MaLop_Chon(List &l){
	readFile(l);
	for(NODE *i=l.pHead;i!=l.pTail;i=i->pNext){	
		for(NODE *j=i->pNext;j!=NULL;j=j->pNext){
			string s1 = i->data.maLop;
			string s2 = j->data.maLop;
			// So Sanh 3 ki tu cuoi cua 2 chuoi Ma Lop
			if(s1.compare(s1.length()-3,3,s2,s2.length()-3,3) >0)  hoanVi(i,j);
			if(s1.compare(s1.length()-3,3,s2,s2.length()-3,3)==0){
				// So Sanh tu dau
				if(s1.compare(0,s1.length()-3,s2,0,s2.length()-3) > 0) hoanVi(i,j);
				if(s1.compare(0,s1.length()-3,s2,0,s2.length()-3)==0){
					// Sap xep Ten
					if(i->data.Ten.ten > j->data.Ten.ten)  hoanVi(i,j);
					if(i->data.Ten.ten == j->data.Ten.ten){
						string r1 = " ";
						string r2 = " ";
						std::size_t x1 = s1.find(r1);
						std::size_t x2 = s2.find(r2);
						if(s1.compare(x1+1,s1.length()-x1,s2,x2+1,s2.length()-x2) >0) hoanVi(i,j);
						if(s1.compare(x1+1,s1.length()-x1,s2,x2+1,s2.length()-x2)==0){
							// Sap xep ngay sinh
							if(i->data.Date.nam > j->data.Date.nam)  hoanVi(i,j);
							if(i->data.Date.nam == j->data.Date.nam){
								if(i->data.Date.thang > j->data.Date.thang)  hoanVi(i,j);
								if(i->data.Date.thang == j->data.Date.thang){
									if(i->data.Date.ngay > j->data.Date.ngay)  hoanVi(i,j);
									if(i->data.Date.ngay == j->data.Date.ngay){
										// So sanh Diem
										if(i->data.DTBTL > j->data.DTBTL) hoanVi(i,j);
									}
								}
							}
						}
					}
				}	
			}		
		}	
	}
	in_sx(l);	
}
//
void sx_MaLop_Chen(List &l){
	readFile(l);
	for(NODE *i=l.pHead;i!=l.pTail;i=i->pNext){
		NODE *k=i;
		for(NODE *j=i->pNext;j!=NULL;j=j->pNext){
			string s1 = k->data.maLop;
			string s2 = j->data.maLop;
			if(s1.compare(s1.length()-3,3,s2,s2.length()-3,3) >0)  k=j;
			if(s1.compare(s1.length()-3,3,s2,s2.length()-3,3)==0){
				if(s1.compare(0,s1.length()-3,s2,0,s2.length()-3) > 0) k=j;
				if(s1.compare(0,s1.length()-3,s2,0,s2.length()-3) ==0){
					// Sap xep ten
					if(k->data.Ten.ten > j->data.Ten.ten)  k=j;
					if(k->data.Ten.ten == j->data.Ten.ten){
						string r1 = " ";
						string r2 = " ";
						std::size_t x1 = s1.find(r1);
						std::size_t x2 = s2.find(r2);
						if(s1.compare(x1+1,s1.length()-x1,s2,x2+1,s2.length()-x2) >0) k=j;
						if(s1.compare(x1+1,s1.length()-x1,s2,x2+1,s2.length()-x2)==0){
							// Sap xep ngay
							if(k->data.Date.nam > j->data.Date.nam)                   k=j;
							if(k->data.Date.nam == j->data.Date.nam){
								if(k->data.Date.thang > j->data.Date.thang)     k=j;
								if(k->data.Date.thang==j->data.Date.thang){
									if(k->data.Date.ngay > j->data.Date.ngay)  k=j;
									if(k->data.Date.ngay ==j->data.Date.ngay){
										//So sanh diem
										if(k->data.DTBTL > j->data.DTBTL) k=j;
									}
								}
							}
						}
					}
				}
			}
		}
		if(k!=i)  hoanVi(k,i);
	}
	in_sx(l);
}	

// 5.Sap xep theo Diem TBTL
// Chon
void sx_DTBTL_Chon(List &l){
	readFile(l);
	for(NODE *i=l.pHead;i!=l.pTail;i=i->pNext){
		for(NODE *j=i->pNext;j!=NULL;j=j->pNext){
			if(i->data.DTBTL > j->data.DTBTL)  hoanVi(i,j);
		}
	}
	in_sx(l);
}
//Chen
void sx_DTBTL_Chen(List &l){
	readFile(l);
	for(NODE *i=l.pHead;i!=l.pTail;i=i->pNext){
		NODE *k=i;
		for(NODE *j=i->pNext;j!=NULL;j=j->pNext){
			if(k->data.DTBTL > j->data.DTBTL)  k=j;
		}
		if(k->data.DTBTL != i->data.DTBTL)  hoanVi(k,i);
	}
	in_sx(l);
}

// ------------------------------------------------------
//     TIM KIEM

void phanDau(){
	cout<<"\n"<<endl;
	cout<<"		KET QUA TIM KIEM:"<<endl;
	cout<<"		+______________________________________DANH SACH SINH VIEN_________________________________________+"<<endl;
	cout<<"		|                                                                                                  |"<<endl;
	cout<<"		| STT |         HO  VA  TEN            |    MA  LOP    |    MA  SV    |    NGAY  SINH    |  DTBTL  |"<<endl;
	cout<<"		|-----|--------------------------------|---------------|--------------|------------------|---------|";
}
// TIM theo ma lop
void tk_MaLop(List &l){
	HANDLE h;
	h = GetStdHandle(STD_OUTPUT_HANDLE);
	readFile(l);
	string s;
	cout<<" ($) Nhap Ma lop can tim kiem : "; 
	getline(cin,s); std::transform(s.begin(),s.end(),s.begin(), ::toupper); 
	phanDau();	int y=10,t=1;
	for(NODE *p=l.pHead;p!=NULL;p=p->pNext){
		if(s == p->data.maLop){
			gotoxy(16,y); cout<<"| "<<t;
			gotoxy(22,y); cout<<"|    "<<p->data.Ten.ho<<" "<<p->data.Ten.ten;
			gotoxy(55,y); cout<<"|   "; SetConsoleTextAttribute(h,71);
			cout<<p->data.maLop; SetConsoleTextAttribute(h,15);
			gotoxy(71,y); cout<<"|   "<<p->data.maSV;
			gotoxy(86,y); cout<<"|    "<<p->data.Date.ngay<<"/"<<p->data.Date.thang<<"/"<<p->data.Date.nam;
			gotoxy(105,y); cout<<"|  "<<p->data.DTBTL<<setprecision(2)<<fixed;
			gotoxy(115,y); cout<<"|"<<endl;
			cout<<"		|-----|--------------------------------|---------------|--------------|------------------|---------|"<<endl;
			y+=2; t++;	
		}
	}
}
//Tim theo ma SV
void tk_MaSV(List &l){
	HANDLE h;
	h = GetStdHandle(STD_OUTPUT_HANDLE);
	readFile(l);
	string s;
	cout<<" ($) Nhap Ma SV can tim kiem : "; getline(cin,s);
	phanDau(); int y=10,t=1;
	for(NODE *p=l.pHead;p!=NULL;p=p->pNext){
		if(s == p->data.maSV){
			gotoxy(16,y); cout<<"| "<<t;
			gotoxy(22,y); cout<<"|    "<<p->data.Ten.ho<<" "<<p->data.Ten.ten;
			gotoxy(55,y); cout<<"|   "<<p->data.maLop;
			gotoxy(71,y); cout<<"|   ";  SetConsoleTextAttribute(h,71);
			cout<<p->data.maSV; SetConsoleTextAttribute(h,15);
			gotoxy(86,y); cout<<"|    "<<p->data.Date.ngay<<"/"<<p->data.Date.thang<<"/"<<p->data.Date.nam;
			gotoxy(105,y); cout<<"|  "<<p->data.DTBTL<<setprecision(2)<<fixed;
			gotoxy(115,y); cout<<"|"<<endl;
			cout<<"		|-----|--------------------------------|---------------|--------------|------------------|---------|"<<endl;
			y+=2;t++;
		}
	}
}
//Tim kiem theo Ten
void tk_Ten_not(List &l){
	readFile(l);
	HANDLE h;
	h = GetStdHandle(STD_OUTPUT_HANDLE);
	string s;
	cout<<" ($) Nhap thong tin can tim kiem : ";  getline(cin,s);
	xoa(s); xoaGiua(s); inHoa(s); 
	phanDau(); int y=10,t=1;
	for(NODE *p=l.pHead;p;p=p->pNext){
		string s0 = p->data.Ten.ho +" "+p->data.Ten.ten;
		std::size_t  x = s0.find(s);  
		if(s.compare(1,s.length()-1,s0,x+1,s.length()-1)==0){
			gotoxy(16,y); cout<<"| "<<t;
			gotoxy(22,y); cout<<"|    "<<p->data.Ten.ho<<" "<<p->data.Ten.ten;
			SetConsoleTextAttribute(h,71);
			gotoxy(27+x,y); cout<<s; SetConsoleTextAttribute(h,15);
			gotoxy(55,y); cout<<"|   "<<p->data.maLop; 
			gotoxy(71,y); cout<<"|   "<<p->data.maSV;
			gotoxy(86,y); cout<<"|    "<<p->data.Date.ngay<<"/"<<p->data.Date.thang<<"/"<<p->data.Date.nam;
			gotoxy(105,y); cout<<"|  "<<p->data.DTBTL<<setprecision(2)<<fixed;
			gotoxy(115,y); cout<<"|"<<endl;
			cout<<"		|-----|--------------------------------|---------------|--------------|------------------|---------|"<<endl;
			y+=2;t++;	
		}
	}
}
//Tim kiem theo ngay sinh
void tk_NgaySinh(List &l){
	HANDLE h;
	h = GetStdHandle(STD_OUTPUT_HANDLE);
	readFile(l);
	int day,month,year;
	cout<<" ($) Nhap Ngay sinh can tim kiem : ";
	gotoxy(30,2); cout<<"	Ngay:";cin>>day; 
	gotoxy(45,2); cout<<"	Thang:";cin>>month; 
	gotoxy(60,2); cout<<"	Nam:";cin>>year;
	phanDau(); int y=10,t=1;
	for(NODE *p=l.pHead;p!=NULL;p=p->pNext){
		if(day==p->data.Date.ngay && month==p->data.Date.thang && year==p->data.Date.nam){
			gotoxy(16,y); cout<<"| "<<t;
			gotoxy(22,y); cout<<"|    "<<p->data.Ten.ho<<" "<<p->data.Ten.ten;
			gotoxy(55,y); cout<<"|   "<<p->data.maLop;
			gotoxy(71,y); cout<<"|   "<<p->data.maSV;
			gotoxy(86,y); cout<<"|    "; SetConsoleTextAttribute(h,71);
			cout<<p->data.Date.ngay<<"/"<<p->data.Date.thang<<"/"<<p->data.Date.nam; SetConsoleTextAttribute(h,15);
			gotoxy(105,y); cout<<"|  "<<p->data.DTBTL<<setprecision(2)<<fixed;
			gotoxy(115,y); cout<<"|"<<endl;
			cout<<"		|-----|--------------------------------|---------------|--------------|------------------|---------|"<<endl;
			y+=2;t++;			
		}	
	}
}
//Tim kiem theo DTBTL
void tk_DTBTL(List &l){
	HANDLE h;
	h = GetStdHandle(STD_OUTPUT_HANDLE);
	readFile(l); float diem;
	cout<<" ($) Nhap DTBTL can tim kiem : "; cin>>diem;
	phanDau(); int y=10,t=1;
	for(NODE *p=l.pHead;p!=NULL;p=p->pNext){
		if(diem == p->data.DTBTL){
			gotoxy(16,y); cout<<"| "<<t;
			gotoxy(22,y); cout<<"|    "<<p->data.Ten.ho<<" "<<p->data.Ten.ten;
			gotoxy(55,y); cout<<"|   "<<p->data.maLop;
			gotoxy(71,y); cout<<"|   "<<p->data.maSV;
			gotoxy(86,y); cout<<"|    "<<p->data.Date.ngay<<"/"<<p->data.Date.thang<<"/"<<p->data.Date.nam;
			gotoxy(105,y); cout<<"|  "; SetConsoleTextAttribute(h,71);
			cout<<p->data.DTBTL<<setprecision(2)<<fixed; SetConsoleTextAttribute(h,15);
			gotoxy(115,y); cout<<"|"<<endl;
			cout<<"		|-----|--------------------------------|---------------|--------------|------------------|---------|"<<endl;
			y+=2;t++;			
		}
	}
}
// Tim kiem bat ki------------------
void tk(List &l){
	readFile(l);
	HANDLE h;
	h = GetStdHandle(STD_OUTPUT_HANDLE);
	string s;
	cout<<" <";SetConsoleTextAttribute(h,12); cout<<"!";SetConsoleTextAttribute(h,15);cout<<"> Nhap thong tin can tim kiem : "; getline(cin,s);
	phanDau(); int y=10,t=1;
	for(NODE *p=l.pHead;p;p=p->pNext){
		ostringstream Date,Score;
		Date<<p->data.Date.ngay<<"/"<<p->data.Date.thang<<"/"<<p->data.Date.nam;
		Score<<p->data.DTBTL;
		string s1 = Date.str();
		string s2 = Score.str();
		
		if(s==s2){  
			gotoxy(16,y); cout<<"| "<<t;
			gotoxy(22,y); cout<<"|    "<<p->data.Ten.ho<<" "<<p->data.Ten.ten;
			gotoxy(55,y); cout<<"|   "<<p->data.maLop; 
			gotoxy(71,y); cout<<"|   "<<p->data.maSV;
			gotoxy(86,y); cout<<"|    "<<p->data.Date.ngay<<"/"<<p->data.Date.thang<<"/"<<p->data.Date.nam;
			gotoxy(105,y); cout<<"|  ";SetConsoleTextAttribute(h,71);
			cout<<p->data.DTBTL<<setprecision(2)<<fixed;SetConsoleTextAttribute(h,15);
			gotoxy(115,y); cout<<"|"<<endl;
			cout<<"		|-----|--------------------------------|---------------|--------------|------------------|---------|"<<endl;
			y+=2;t++;
		}else{ // Neu la ngay sinh
			if(s==s1){
				gotoxy(16,y); cout<<"| "<<t;
				gotoxy(22,y); cout<<"|    "<<p->data.Ten.ho<<" "<<p->data.Ten.ten;
				gotoxy(55,y); cout<<"|   "<<p->data.maLop; 
				gotoxy(71,y); cout<<"|   "<<p->data.maSV;
				gotoxy(86,y); cout<<"|    ";SetConsoleTextAttribute(h,71);
				cout<<p->data.Date.ngay<<"/"<<p->data.Date.thang<<"/"<<p->data.Date.nam;SetConsoleTextAttribute(h,15);
				gotoxy(105,y); cout<<"|  "<<p->data.DTBTL<<setprecision(2)<<fixed;
				gotoxy(115,y); cout<<"|"<<endl;
				cout<<"		|-----|--------------------------------|---------------|--------------|------------------|---------|"<<endl;
				y+=2;t++;
			}else{
					// Neu la ho ten
			if(s.length()>=2){
				xoa(s); xoaGiua(s); inHoa(s);
				string s3 = p->data.Ten.ho +" "+ p->data.Ten.ten;
				std::size_t x1 = s3.find(s);
				
				if(s.compare(1,s.length()-1,s3,x1+1,s.length()-1)==0){	
					gotoxy(16,y); cout<<"| "<<t;
					gotoxy(22,y); cout<<"|    "<<p->data.Ten.ho<<" "<<p->data.Ten.ten;
					SetConsoleTextAttribute(h,71);
					gotoxy(27+x1,y); cout<<s; SetConsoleTextAttribute(h,15);
					gotoxy(55,y); cout<<"|   "<<p->data.maLop; 
					gotoxy(71,y); cout<<"|   "<<p->data.maSV;
					gotoxy(86,y); cout<<"|    "<<p->data.Date.ngay<<"/"<<p->data.Date.thang<<"/"<<p->data.Date.nam;
					gotoxy(105,y); cout<<"|  "<<p->data.DTBTL<<setprecision(2)<<fixed;
					gotoxy(115,y); cout<<"|"<<endl;
					cout<<"		|-----|--------------------------------|---------------|--------------|------------------|---------|"<<endl;
					y+=2;t++;	
				}
				else{ // Neu la ma lop
					std::transform(s.begin(),s.end(),s.begin(), ::toupper); 
					std::size_t x2 = p->data.maLop.find(s);
					if(s.compare(1,s.length()-1,p->data.maLop,x2+1,s.length()-1)==0){
						gotoxy(16,y); cout<<"| "<<t;
						gotoxy(22,y); cout<<"|    "<<p->data.Ten.ho<<" "<<p->data.Ten.ten;
						gotoxy(55,y); cout<<"|   "<<p->data.maLop; SetConsoleTextAttribute(h,71);
						gotoxy(59+x2,y); cout<<s;  SetConsoleTextAttribute(h,15); 
						gotoxy(71,y); cout<<"|   "<<p->data.maSV;
						gotoxy(86,y); cout<<"|    "<<p->data.Date.ngay<<"/"<<p->data.Date.thang<<"/"<<p->data.Date.nam;
						gotoxy(105,y); cout<<"|  "<<p->data.DTBTL<<setprecision(2)<<fixed;
						gotoxy(115,y); cout<<"|"<<endl;
						cout<<"		|-----|--------------------------------|---------------|--------------|------------------|---------|"<<endl;
						y+=2;t++;	
					}else{ // Neu la ma SV
						std::size_t x3 = p->data.maSV.find(s);
						if(s.compare(1,s.length()-1,p->data.maSV,x3+1,s.length()-1)==0){
							gotoxy(16,y); cout<<"| "<<t;
							gotoxy(22,y); cout<<"|    "<<p->data.Ten.ho<<" "<<p->data.Ten.ten;
							gotoxy(55,y); cout<<"|   "<<p->data.maLop; 
							gotoxy(71,y); cout<<"|   "<<p->data.maSV;SetConsoleTextAttribute(h,71);
							gotoxy(75+x3,y); cout<<s; SetConsoleTextAttribute(h,15);
							gotoxy(86,y); cout<<"|    "<<p->data.Date.ngay<<"/"<<p->data.Date.thang<<"/"<<p->data.Date.nam;
							gotoxy(105,y); cout<<"|  "<<p->data.DTBTL<<setprecision(2)<<fixed;
							gotoxy(115,y); cout<<"|"<<endl;
							cout<<"		|-----|--------------------------------|---------------|--------------|------------------|---------|"<<endl;
							y+=2;t++;
						}
						else{
							gotoxy(16,y); cout<<"| "<<t;
							gotoxy(22,y); cout<<"|    "<<p->data.Ten.ho<<" "<<p->data.Ten.ten;
							gotoxy(55,y); cout<<"|   "<<p->data.maLop;
							gotoxy(71,y); cout<<"|   "<<p->data.maSV;
							gotoxy(86,y); cout<<"|    "<<p->data.Date.ngay<<"/"<<p->data.Date.thang<<"/"<<p->data.Date.nam;
							gotoxy(105,y); cout<<"|  "<<p->data.DTBTL<<setprecision(2)<<fixed;
							gotoxy(115,y); cout<<"|"<<endl;
							cout<<"		|-----|--------------------------------|---------------|--------------|------------------|---------|"<<endl;
							y+=2;	t++;
						}		
					}
				}
				}
			}
		}	
	}
}


//---------------------------------THONG KE----------------------

// Doc
int docDSSV(List &l){
	readFile(l); 
	int dem=0;
	for(NODE *p=l.pHead;p;p=p->pNext){
		dem++;
	}
	return dem;
}
//----
//void tke_SoLuong(List &l){
//	readFile(l);
//	int n=docDSSV(l);
//	// Sap xep
//	for(NODE *i=l.pHead;i!=l.pTail;i=i->pNext){
//		for(NODE *j=i->pNext;j;j=j->pNext){
//			if(i->data.maLop > j->data.maLop)  hoanVi(i,j);
//		}
//	}
//	NODE *i=l.pHead;
//	thongKe tk[n];
//	int y=6 ,k=0;
//	//cout<<endl;
//	cout<<"			+_____________________________________________________________________________________+"<<endl;
//	cout<<"			 |                      |                                       |                    |"<<endl;
//	cout<<"			 |        MA LOP        |               TEN LOP                 |    SO SINH VIEN    |"<<endl;
//	cout<<"			 |----------------------|---------------------------------------|--------------------|"<<endl;	
//	
//	while(i!=l.pTail){
//		int dem = 1;
//		for(NODE *j=i->pNext; j ;j=j->pNext){
//			if(i->data.maLop == j->data.maLop) dem++;
//		}
//		tk[k].Lop.insert(0,i->data.maLop);
//		tk[k].soSV = dem;
//		
//		gotoxy(25,y); cout<<"|    "<<tk[k].Lop;
//		///
//		if(tk[k].Lop=="CNTT16A"){
//			gotoxy(48,y); cout<<"|    Cong Nghe Thong Tin 16A";
//		}else{
//			if(tk[k].Lop=="CNTT16B"){
//				gotoxy(48,y); cout<<"|    Cong Nghe Thong Tin 16B";
//			}else{
//				if(tk[k].Lop=="TNCNTT16B"){
//					gotoxy(48,y); cout<<"|   Tai Nang Cong Nghe Thong Tin 16B";
//				}else{
//					if(tk[k].Lop=="CNTT15B"){
//						gotoxy(48,y); cout<<"|    Cong Nghe Thong Tin 15B";
//					}else{
//						if(tk[k].Lop=="KHMT16A"){
//							gotoxy(48,y); cout<<"|    Khoa Hoc May Tinh 16A";
//						}else{
//							if(tk[k].Lop=="XD14C"){
//								gotoxy(48,y); cout<<"|    Xay Dung 14C";
//							}else{
//								if(tk[k].Lop=="TDH17B"){
//									gotoxy(48,y); cout<<"|    Tu Dong Hoa 17B";
//								}else {
//									if(tk[k].Lop=="CNTT16C"){
//										gotoxy(48,y); cout<<"|    Cong Nghe Thong Tin 16C";
//									}else{
//										if(tk[k].Lop=="CNPM16A"){
//											gotoxy(48,y); cout<<"|    Cong Nghe Phan Mem 16A";
//										}else{
//											if(tk[k].Lop=="MMT16B"){
//												gotoxy(48,y); cout<<"|    Mang May Tinh 16B";
//											}else{
//												gotoxy(48,y); cout<<"|    "<<tk[k].Lop;
//											}
//										}
//									}
//								}
//							}
//						}
//					}
//				}  
//			} 
//		}
//		gotoxy(88,y); cout<<"|        "<<tk[k].soSV;
//		gotoxy(109,y); cout<<"|"<<endl;
//		
//		if(dem==1) i=i->pNext;
//		else{
//			if(dem==2) i=i->pNext->pNext;
//			else{
//				if(dem==3) i=i->pNext->pNext->pNext;
//				else{
//					if(dem==4) i=i->pNext->pNext->pNext->pNext;
//					else{
//						if(dem==5) i=i->pNext->pNext->pNext->pNext->pNext;
//						else{
//							if(dem==6) i=i->pNext->pNext->pNext->pNext->pNext->pNext;
//							else{
//								if(dem==7) i=i->pNext->pNext->pNext->pNext->pNext->pNext->pNext;
//								else{
//									if(dem==8) i=i->pNext->pNext->pNext->pNext->pNext->pNext->pNext->pNext;
//									else{
//										if(dem==9) i=i->pNext->pNext->pNext->pNext->pNext->pNext->pNext->pNext->pNext;
//									}
//								}
//							}
//						}
//					}
//				}
//			}
//		}
//		y+=2;k++;
//		cout<<"			 |----------------------|---------------------------------------|--------------------|"<<endl;
//	}
//	cout<<"			 |                                                              |                    |"<<endl;
//	cout<<"			 |                          TONG                                |        "<<n<<"          |"<<endl;
//	cout<<"			 +===================================================================================+"<<endl;
//}



////------
void tke_SoLuong(List &l){
	readFile(l); 
	int n=docDSSV(l);
	struct sinhVien sv[n];
	NODE *p = l.pHead;
	for(int i=0;i<n;i++){
		sv[i].Date = p->data.Date;
		sv[i].DTBTL = p->data.DTBTL;
		sv[i].maLop = p->data.maLop;
		sv[i].maSV = p->data.maSV;
		sv[i].Ten = p->data.Ten;
		p = p->pNext;	
	} //sx
	for(int i=0;i<n-1;i++){
		for(int j=i+1;j<n;j++){
			if(sv[i].maLop.compare(sv[j].maLop) >0){
				sinhVien tinh;
				tinh = sv[i];
				sv[i] = sv[j];
				sv[j] = tinh;
			}
		}	  
	}
	// tk
	struct thongKe tk[n];

	cout<<"			+_____________________________________________________________________________________+"<<endl;
	cout<<"			 |                      |                                       |                    |"<<endl;
	cout<<"			 |        MA LOP        |               TEN LOP                 |    SO SINH VIEN    |"<<endl;
	cout<<"			 |----------------------|---------------------------------------|--------------------|"<<endl;
	int i=0, k=0, y=6;
	while(i<n){
		int dem=1;
		for(int j=i+1;j<n;j++){
			if(sv[i].maLop==sv[j].maLop) dem++;
		}
		tk[k].Lop.insert(0,sv[i].maLop);
		tk[k].soSV = dem;
		gotoxy(25,y); cout<<"|    "<<tk[k].Lop;
		///
		if(tk[k].Lop=="CNTT16A"){
			gotoxy(48,y); cout<<"|    Cong Nghe Thong Tin 16A";
		}else{
			if(tk[k].Lop=="CNTT16B"){
				gotoxy(48,y); cout<<"|    Cong Nghe Thong Tin 16B";
			}else{
				if(tk[k].Lop=="TNCNTT16B"){
					gotoxy(48,y); cout<<"|    Tai Nang Cong Nghe Thong Tin 16B";
				}else{
					if(tk[k].Lop=="CNTT15B"){
						gotoxy(48,y); cout<<"|    Cong Nghe Thong Tin 15B";
					}else{
						if(tk[k].Lop=="KHMT16A"){
							gotoxy(48,y); cout<<"|    Khoa Hoc May Tinh 16A";
						}else{
							if(tk[k].Lop=="XD14C"){
								gotoxy(48,y); cout<<"|    Xay Dung 14C";
							}else{
								if(tk[k].Lop=="TDH17B"){
									gotoxy(48,y); cout<<"|    Tu Dong Hoa 17B";
								}else {
									if(tk[k].Lop=="CNTT16C"){
										gotoxy(48,y); cout<<"|    Cong Nghe Thong Tin 16C";
									}else{
										if(tk[k].Lop=="CNPM16A"){
											gotoxy(48,y); cout<<"|    Cong Nghe Phan Mem 16A";
										}else{
											if(tk[k].Lop=="MMT16B"){
												gotoxy(48,y); cout<<"|    Mang May Tinh 16B";
											}else{
												gotoxy(48,y); cout<<"|    "<<tk[k].Lop;
											}
										}
									}
								}
							}
						}
					}
				}  
			} 
		}
		gotoxy(88,y); cout<<"|        "<<tk[k].soSV;
		gotoxy(109,y); cout<<"|"<<endl;
		i = i+dem;
		k++; 
		y+=2;
		cout<<"			 |----------------------|---------------------------------------|--------------------|"<<endl;
	}
	cout<<"			 |                                                              |                    |"<<endl;
	cout<<"			 |                          TONG                                |       "<<n<<"          |"<<endl;
	cout<<"			 +===================================================================================+"<<endl;
	

	// So luong xs,g,k,tb,y cua tung lop
	for(int i=0;i<k;i++){
		int xs=0; int g=0; int kh=0; int tb=0;int ye=0;
		//int dem =0;
		for(int j=0;j<n;j++){
			if(tk[i].Lop == sv[j].maLop)
			{
				if(sv[j].DTBTL >= 3.6)  xs++;
				else{
					if(sv[j].DTBTL >=3.2 && sv[j].DTBTL <3.6) g++;
					else{
						if(sv[j].DTBTL >=2.5 && sv[j].DTBTL <3.2) kh++;
						else{
							if(sv[j].DTBTL >=2 && sv[j].DTBTL <2.5) tb++;
							else{
								if(sv[j].DTBTL <2) ye++;
							}
						}
					}
				}
			}
		}
		tk[i].sl_XS = xs;
		tk[i].sl_Gioi = g;
		tk[i].sl_Kha = kh;
		tk[i].sl_TB = tb;
		tk[i].sl_Yeu = ye;
	}
	// Tong SV xs,g,k,tb,y
	int tong_xs=0,tong_g=0,tong_k=0,tong_tb=0,tong_y=0;
	for(int i=0;i<k;i++){
		tong_xs += tk[i].sl_XS;
		tong_g += tk[i].sl_Gioi;
		tong_k += tk[i].sl_Kha;
		tong_tb += tk[i].sl_TB;
		tong_y += tk[i].sl_Yeu;
		
	}
	// Tinh phan tram
	float tl_xs,tl_g,tl_k,tl_tb,tl_y;  //  Ti le cua tong
	for(int i=0;i<k;i++){
		// Ti Le cua tung lop
		tk[i].tle_XS = (float)tk[i].sl_XS / tk[i].soSV *100;
		tk[i].tle_G = (float)tk[i].sl_Gioi / tk[i].soSV *100;
		tk[i].tle_K = (float)tk[i].sl_Kha / tk[i].soSV *100;
		tk[i].tle_TB = (float)tk[i].sl_TB / tk[i].soSV *100;
		tk[i].tle_Y = (float)tk[i].sl_Yeu / tk[i].soSV *100;
		// Ti le cua tong
		tl_xs = (float)tong_xs / n *100;
		tl_g = (float)tong_g / n *100;
		tl_k = (float)tong_k / n *100;
		tl_tb = (float)tong_tb / n *100;
		tl_y = (float)tong_y / n *100;
		
	}
	
	
	cout<<"\n"<<endl;
	cout<<"	-----------------------------------------------------------------------------------------------------------------"<<endl;
	cout<<"	|               |     XUAT SAC      |      GIOI       |       KHA         |    TRUNG BINH     |      YEU        |"<<endl;
	cout<<"	|     MA LOP    |___________________|_________________|___________________|___________________|_________________|"<<endl;
	cout<<"	|               |    SL   |    %    |   SL   |    %   |   SL   |    %     |    SL   |    %    |   SL   |    %   |"<<endl;
	cout<<"	|---------------|-------------------|-----------------|-------------------|-------------------|-----------------|"<<endl;
	int y0=40;
	for(int i=0;i<k;i++){
		cout<<"	|  "<<tk[i].Lop<<setprecision(2)<<fixed; 
		gotoxy(24,y0); cout<<"|   "<<tk[i].sl_XS;
		gotoxy(34,y0); cout<<"|  "<<tk[i].tle_XS;
		gotoxy(44,y0); cout<<"|   "<<tk[i].sl_Gioi;
		gotoxy(53,y0); cout<<"|  "<<tk[i].tle_G;
		gotoxy(62,y0); cout<<"|   "<<tk[i].sl_Kha;
		gotoxy(71,y0); cout<<"|  "<<tk[i].tle_K;
		gotoxy(82,y0); cout<<"|   "<<tk[i].sl_TB;
		gotoxy(92,y0); cout<<"|  "<<tk[i].tle_TB;
		gotoxy(102,y0); cout<<"|   "<<tk[i].sl_Yeu;
		gotoxy(111,y0); cout<<"| "<<tk[i].tle_Y;
		gotoxy(120,y0); cout<<"|"<<endl;
		cout<<"	|---------------|---------+---------|--------+--------|--------+----------|---------+---------|--------+--------|"<<endl;
		y0+=2;
	}
	cout<<"	|               |         |         |        |        |        |          |         |         |        |        |"<<endl;
	cout<<"	|    TONG       |"<<setprecision(2)<<fixed
	<<setw(5)<<tong_xs<<setw(5)<<"|"<<setw(6)<<tl_xs<<setw(4)<<"|"
	<<setw(4)<<tong_g<<setw(5)<<"|"<<setw(6)<<tl_g<<setw(3)<<"|"
	<<setw(4)<<tong_k<<setw(5)<<"|"<<setw(7)<<tl_k<<setw(4)<<"|"
	<<setw(5)<<tong_tb<<setw(5)<<"|"<<setw(6)<<tl_tb<<setw(4)<<"|"
	<<setw(4)<<tong_y<<setw(5)<<"|"<<setw(6)<<tl_y<<setw(3)<<"|"<<endl;
	cout<<"	|_______________|_________|_________|________|________|________|__________|_________|_________|________|________|"<<endl;
	
}
	





// Menu chon
int MENU(List &l){
	HANDLE h;
	h = GetStdHandle(STD_OUTPUT_HANDLE);
	while(1){	
		
		int n;
		SetConsoleTextAttribute(h,15);
		cout<<endl;
		gotoxy(120,2); cout<<"_____________________________________________"<<endl;
		gotoxy(120,3); cout<<"|                                           |"<<endl;
		gotoxy(120,4); cout<<"|";SetConsoleTextAttribute(h,10);
		cout<<"      CHUONG TRINH QUAN LI SINH VIEN       "; SetConsoleTextAttribute(h,15);cout<<"|"<<endl;
		gotoxy(120,5); cout<<"|          ___                              |"<<endl;
		gotoxy(120,6); cout<<"|         ( 1 ) : Them moi ho so            |"<<endl;
		gotoxy(120,7); cout<<"|          ___                              |"<<endl;		
		gotoxy(120,8); cout<<"|         ( 2 ) : In ho so                  |"<<endl;
		gotoxy(120,9); cout<<"|          ___                              |"<<endl;
		gotoxy(120,10);cout<<"|         ( 3 ) : Sap xep                   |"<<endl;
		gotoxy(120,11);cout<<"|          ___                              |"<<endl;
		gotoxy(120,12);cout<<"|         ( 4 ) : Tim kiem                  |"<<endl;
		gotoxy(120,13);cout<<"|          ___                              |"<<endl;
		gotoxy(120,14);cout<<"|         ( 5 ) : Thong ke                  |"<<endl;
		gotoxy(120,15);cout<<"|          ___                              |"<<endl;
		gotoxy(120,16);cout<<"|         ( 6 ) : Thoat                     |"<<endl;
		gotoxy(120,17);cout<<"|                                           |"<<endl;
		gotoxy(120,18);cout<<"|                                           |"<<endl;
		gotoxy(120,19);cout<<"|___________________________________________|"<<endl;

		n=getch();
		switch(n){
			
			case '1':{
				system("cls");
				SetConsoleTextAttribute(h,14);
				cout<<"\n		  THEM HO SO  \n"<<endl;
				SetConsoleTextAttribute(h,15);
				themHoSo();
				system("cls");
				break;
			}
			case '2':{
				system("cls");
				SetConsoleTextAttribute(h,14);
				cout<<"\n		 IN HO SO  \n"<<endl; SetConsoleTextAttribute(h,15);
				inDanhSach(l);
				break;
			}
			case '3':{
				system("cls");
				SetConsoleTextAttribute(h,14);
				cout<<"\n		_//_ "<<endl;
				cout<<"  		|@@|  SAP XEP"<<endl; SetConsoleTextAttribute(h,15);
				cout<<"\n					< 1 > : Sap xep theo Ma Lop.\n";
				cout<<"\n				< 2 > : Sap xep theo Ma Sinh Vien.\n";
				cout<<"\n			< 3 > : Sap xep theo Ho va Ten.\n";
				cout<<"\n		< 4 > : Sap xep theo Ngay sinh.\n";
				cout<<"\n	< 5 > : Sap xep thep DTBTL."<<endl;
					int t=getch();
					switch(t){
						case '1':{
							system("cls");
							SetConsoleTextAttribute(h,14);
							cout<<"\n		  SAP XEP  \n"<<endl; SetConsoleTextAttribute(h,15);
							cout<<"\n	1 : Sap xep theo Ma Lop."<<endl;
							cout<<"\n					-> 1) : Sap xep Chon."<<endl;
							cout<<"\n					-> 2) : Sap xep Chen.";
							int i1=getch();
							switch(i1){
								case '1':{
									system("cls");
									sx_MaLop_Chon(l);
									break;
								}
								case '2':{
									system("cls");
									sx_MaLop_Chen(l);
									break;
								}
							}
							break;
						}
						case '2':{
							system("cls");
							SetConsoleTextAttribute(h,14);
							cout<<"\n		  SAP XEP  \n"<<endl;SetConsoleTextAttribute(h,15);
							cout<<"\n  2 : Sap xep theo Ma Sinh Vien."<<endl;
							cout<<"\n			-> 1) : Sap xep Chon."<<endl;						
							cout<<"\n			-> 2) : Sap xep Chen.";
							int i2=getch();
							switch(i2){
								case '1':{
									system("cls");
									sx_MaSV_Chon(l);
									break;
								}
								case '2':{
									system("cls");
									sx_MaSV_Chen(l);
									break;
								}								
							}
							break;
						}
						case '3':{
							system("cls");
							SetConsoleTextAttribute(h,14);
							cout<<"\n		  SAP XEP  \n"<<endl;SetConsoleTextAttribute(h,15);
							cout<<"\n  3 : Sap xep theo Ho va Ten."<<endl;							
							cout<<"\n			-> 1) : Sap xep Chon."<<endl;							
							cout<<"\n			-> 2) : Sap xep Chen.";
							int i3=getch();
							switch(i3){
								case '1':{
									system("cls");
									sx_Ten_Chon(l);
									break;
								}
								case '2':{
									system("cls");
									sx_Ten_Chen(l);
									break;
								}
							}
							break;
						}
						case '4':{
							system("cls");
							SetConsoleTextAttribute(h,14);
							cout<<"\n		  SAP XEP  \n"<<endl;SetConsoleTextAttribute(h,15);
							cout<<"\n  4 : Sap xep theo Ngay sinh."<<endl;							
							cout<<"\n			-> 1) : Sap xep Chon."<<endl;							
							cout<<"\n			-> 2) : Sap xep Chen.";
							int i4=getch();
							switch(i4){
								case '1':{
									system("cls");
									sx_NgaySinh_Chon(l);
									break;
								}
								case '2':{
									system("cls");
									sx_NgaySinh_Chen(l);	
									break;
								}								
							}
							break;
						}
						case '5':{
							system("cls");
							SetConsoleTextAttribute(h,14);
							cout<<"\n		@  SAP XEP $\n"<<endl;SetConsoleTextAttribute(h,15);
							cout<<"\n	5 : Sap xep theo Diem TBTL."<<endl;
							cout<<"\n			-> 1) : Sap xep Chon."<<endl;
							cout<<"\n			-> 2) : Sap xep Chen.";
							int i5=getch();
							switch(i5){
								case '1':{
									system("cls");
									sx_DTBTL_Chon(l);
									break;
								}
								case '2':{
									system("cls");
									sx_DTBTL_Chen(l);
									break;
								}
							}
							break;
						}							
					}
				break;
			}
			case '4':{
				system("cls");
				SetConsoleTextAttribute(h,14);
				cout<<"\n"<<endl;
				cout<<"	TIM KIEM"<<endl; SetConsoleTextAttribute(h,15);	
				cout<<"		 {1} : Tim kiem theo Ma Lop.\n"<<endl;
				cout<<"		 {2} : Tim kiem theo Ma SV.\n"<<endl;	
				cout<<"		 {3} : Tim kiem theo Ho va Ten.\n"<<endl;				
				cout<<"		 {4} : Tim kiem theo Ngay sinh.\n"<<endl;				
				cout<<"		 {5} : Tim kiem theo DTBTL.\n"<<endl;				
				cout<<"		*{6} : Tim kiem bat ki."<<endl;
				int v=getch();
				switch(v){
					case '1':{
						system("cls");
						cout<<"\n	{ 1 } : Tim kiem theo Ma Lop."<<endl;
						tk_MaLop(l);
						break;
					}
					case '2':{
						system("cls");
						cout<<"\n	{ 2 } : Tim kiem theo Ma SV."<<endl;
						tk_MaSV(l);
						break;
					}
					case '3':{
						system("cls");
						cout<<"\n	{ 3 } : Tim kiem theo Ho va Ten."<<endl;
						tk_Ten_not(l);
						break;
					}
					case '4':{
						system("cls");
						cout<<"\n	{ 4 } : Tim kiem theo Ngay sinh."<<endl;
						tk_NgaySinh(l);
						break;
					}
					case '5':{
						system("cls");
						cout<<"\n	{ 5 } : Tim kiem theo DTBTL."<<endl;
						tk_DTBTL(l);
						break;
					}
					case '6':{
						system("cls");
						cout<<"\n	*{ 6 } : Tim kiem bat ki."<<endl;
						tk(l);
						break;
					}
					break;
				}
				break;
			}
			case '5':{
				system("cls"); SetConsoleTextAttribute(h,14);
				cout<<"\n	THONG KE"<<endl; SetConsoleTextAttribute(h,15);
				tke_SoLuong(l);
				break;
			}
			case '6':{
				system("cls");
				cout<<"	Ban da thoat"<<endl;
				return 0;
			}
			default:{
				system("cls");
				cout<<"\n	Tinh nang chua cap nhat!"<<endl;
				cout<<"\n Bam phim bat ki de Tiep tuc";
				int c=getch();
				system("cls");
				if(c==13) MENU(l);
				else MENU(l);
				break;
			}
		}
	}	
}
int main(){	
	
	List l;
	MENU(l);

	return 0;
}

