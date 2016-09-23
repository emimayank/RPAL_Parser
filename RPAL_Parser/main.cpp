#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <stack>
using namespace std;
class Token{
    public:
        string value;
        string type;
};
class Node {
private:
    string token;
	Node *child;
	Node *sibling;
public:

    void setToken(string t){
        this->token=t;
    }
    string getToken(){
        return token;
    }
    void setChild(Node *child){
        this->child=child;
    }
    Node* getChild(){
        return child;
    }
    void setSibling(Node *sibling){
        this->sibling=sibling;
    }
    Node* getSibling(){
        return sibling;
    }
};
std::vector<std::string> alphabets;
std::vector<std::string> nums;
std::vector<std::string> operators;
std::vector<std::string> spaces;
std::vector<std::string> punct;
std::vector<std::string> keywords;
string line;
ifstream myfile ("example.txt");
Token token;
Token identifyTokennType();
std::stack<Node*> mystack;
void modifyFile();
void buildTree(string root, int n);
void fillVectors();
void startParse();
void read(string incoming);
void preOrder(Node n, int level);
void printAST();
void E();
void D();
void Vb();
void Ew();
void Da();
void Dr();
void Db();
void Vl();
void T();
void Ta();
void Tc();
void B();
void Bt();
void Bs();
void Bp();
void A();
void At();
void Af();
void Ap();
void R();
void Rn();
int main(){
  Token token;
  //append_space();
  modifyFile();
  if (myfile.is_open()){
    fillVectors();
    startParse();
    myfile.close();
    //remove("example.txt");
  }
  else cout << "Unable to open file";
}
void modifyFile(){
    string line;
ofstream wfile;
  wfile.open ("example.txt");
ifstream myfile ("C:\\Course Video Lectures\\Assignment\\rpal\\tests\\Treepicture");
  if (myfile.is_open())
  {
    while ( getline (myfile,line) )
    {
        line=line+' '+'\n';
      wfile << line;
    }
    myfile.close();
    wfile.close();
  }
  else{
    cout<<"Unable to open File";
    //EXIT_FAILURE;
  }
}
void startParse(){
    getline (myfile,line);
    //line=line+' ';
    token=identifyTokennType();
    E();
    if(token.value==""){
        token.type="EOF";
    }
    if (token.type=="EOF") {	//EOF reached
        printAST();
    }
}
void preOrder(Node *n, int level) {
    string dot = "";
	for (int i = 0 ; i < level ; i++)
		dot = dot + ".";
		if(n!=NULL && n->getToken().length()!=0){
            cout<<dot+""+n->getToken()<<endl;
		}
		else{
            return;
		}
	if (n->getChild() != NULL) {
		preOrder(n->getChild(), level+1);
	}
	if (n->getSibling() != NULL) {
		preOrder(n->getSibling(), level);
	}
}
void printAST() {
    Node *ast = mystack.top(); //change2
 	preOrder(ast, 0);
}
void read(string incoming){
    if((std::find(keywords.begin(), keywords.end(), token.value) == keywords.end()) &&(token.type=="IDENTIFIER" ||
       token.type=="INTEGER" || token.type=="STRING"))
        buildTree(token.value, 0);
    token=identifyTokennType();
}
void buildTree(string root, int n) {
    int i=0;
    Node *temp = new Node();//
    Node *r = new Node();//    change4
    Node *sib = new Node();//
    string s;
    if(n==0 && token.type=="IDENTIFIER" && (std::find(keywords.begin(), keywords.end(), root) == keywords.end())){
            if(root=="nil" || root=="true" || root=="false" || root=="dummy"){
               s="<"+root+">";
            }else{
                s="<ID:"+root+">";
            }

    }
    else if(n==0 && token.type=="INTEGER"){
        s = "<INT:"+root+">";
    }
    else if(n==0 && token.type=="STRING" && (std::find(keywords.begin(), keywords.end(), root) == keywords.end())){
        s = "<STR:"+root+">";
    }
    else{
        s=root;
    }
   while(i<n){
        //if(!mystack.empty()){
            sib=mystack.top();
            mystack.pop();
        //}
        sib->setSibling(temp); //change5
        temp=sib;
        i++;
    }
    r->setToken(s);
    r->setChild(temp); // change6
    r->setSibling(NULL);
    mystack.push(r);
}
Token identifyTokennType(){
    Token t;
    bool fin;
    string fnd;
    do{
        fin=false;
        char f=line[0];
        fnd="";
        fnd=fnd+f;
        if(std::find(alphabets.begin(), alphabets.end(), fnd) != alphabets.end()) {
            t.type="IDENTIFIER";
            while (true){
                t.value=t.value+f;
                line=line.substr(1);
                f=line[0];
                fnd="";
                fnd=fnd+f;
                if (line.length() == 0) {
					line = "";
					break;
				}
				if(std::find(alphabets.begin(), alphabets.end(), fnd) != alphabets.end())
					continue;
				if(std::find(nums.begin(), nums.end(), fnd) != nums.end())
					continue;
				else if (f == '_')
					continue;
				else
					break;
            }
        }
        else if(std::find(nums.begin(), nums.end(), fnd) != nums.end()){
            t.type="INTEGER";
            while(true){
                t.value=t.value+f;
                //cout<<t.value;
                line=line.substr(1);
                f=line[0];
                fnd="";
                fnd=fnd+f;
                if (line.length() == 0) {
					line = "";
					break;
				}
				if(std::find(nums.begin(), nums.end(), fnd) != nums.end()){
                    continue;
				}
				else{
                    break;
				}
            }
        }
        else if(line[0]=='/' && line[1]=='/'){
            t.type="DELETE";
            getline (myfile,line);
            //line=line+' ';
            if(line==" "){
                t.value="";
            }
            fin=true;
        }
        else if(std::find(operators.begin(), operators.end(), fnd) != operators.end()){
            t.type="OPERATOR";
            while(true){
                t.value=t.value+f;
                line=line.substr(1);
                f=line[0];
                fnd="";
                fnd=fnd+f;
                if(line.length()==0){
                    line="";
                    break;
                }
                if(std::find(operators.begin(), operators.end(), fnd) != operators.end()){
                    continue;
                }
                else{
                    break;
                }
            }
        }
        else if(line[0]=='\''){
            t.type="STRING";
            while(true){
                t.value=t.value+f;
                line=line.substr(1);
                f=line[0];
                fnd="";
                fnd=fnd+f;
                if (line.length() == 0) {
                    line = "";
                    break;
                }
                if(line[0]=='\\'){
                    f=line[0];
                    line=line.substr(1);
                    t.value=t.value+f;
                    f=line[0];
                    line=line.substr(1);
                    t.value=t.value+f;
                }
                if(line[0] == '\''){
                    f=line[0];
                    line=line.substr(1);
                    t.value=t.value+f;
                    if (line.length() == 0)
                        line = "";
						break;
                    }
                }
            }
            else if(f==' ' || f=='\t'||f== '\n'){
                t.type="DELETE";
                line=line.substr(1);
                if(line.length()==0){
                    getline (myfile,line);
                }
                if(myfile.eof()){
                    t.value="";
                }
                fin=true;
            }
            else if(std::find(punct.begin(), punct.end(), fnd) != punct.end()){
                t.type="PUNCTUATIONS";
                t.value=t.value+f;
                line=line.substr(1);
                f=line[0];
                fnd="";
                fnd=fnd+f;
                if(line.length()==0){
                    line="";
                }
            }
            if(f=='\0'){
                getline(myfile,line);
                if(myfile.eof() && t.value.length()==0){
                    t.value="";
                }
            }
    }while(fin==true);
    //cout<<token.value+" "+token.type<<endl;
    return t;
}
void fillVectors(){
        string al[52]=

{"a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z",


"A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z"};
        alphabets.assign(al, al + sizeof al / sizeof al[0]);

        string nu[10]={"0","1","2","3","4","5","6","7","8","9"};
        nums.assign(nu, nu + sizeof nu / sizeof nu[0]);

        string op[26]={"@","+","-","*","/","!","<",">","&",".","[","]","{","}","?","\"","^","_",":","=","~","|","$",
                       "#","%","`"};
        operators.assign(op,op+sizeof op / sizeof op[0]);

        string sp[3]={" ", "\t", "\n"};
        spaces.assign(sp,sp+sizeof sp / sizeof sp[0]);

        string pu[4]={"(", ")", ";", ","};
        punct.assign(pu, pu+sizeof pu / sizeof pu[0]);

        string ke[16]={"let","fn","in","within","rec","where","aug","and","or","not","gr", "ge", "ls", "le", "eq", "ne"};/*,"nil","dummy","true","false"*/
        keywords.assign(ke,ke+ sizeof ke / sizeof ke[0]);
}
void E(){
    if(token.value=="let"){
        read("let");
        D();
        read("in");
        E();
        buildTree("let",2);
    }
    else if(token.value=="fn"){
        read("fn");
        int n=0;
        do{
            Vb();
            n++;
        }while((token.type=="IDENTIFIER") | (token.value=="("));
        read(".");
        E();
        buildTree("lambda",n+1);
    }
    else{
        Ew();
    }
}
void D(){
    Da();
    if (token.value=="within") {
        read("within");
        D();
        buildTree("within", 2);
    }
}
void Vb(){
    if (token.type=="IDENTIFIER")
		read(token.value);
	else if (token.value=="(") {
		read("(");
		if (token.value==")") {
            read(")");
            buildTree("()", 2);
        }
		else {
			Vl();
			read(")");
		}
    }
}
void Ew(){
    T();
    if (token.value=="where") {
        read("where");
        Dr();
        buildTree("where", 2);
    }
}
void T(){
    Ta();
    int n=0;
    while (token.value==",") {
        read(",");
        Ta();
        n++;
    }
    if (n > 0) {
        buildTree("tau", n+1);
    }
}
void Ta(){
    Tc();
	while (token.value=="aug") {
		read("aug");
		Tc();
		buildTree("aug", 2);
	}
}
void Tc(){
    B();
	if (token.value=="->") {
		read("->");
		Tc();
			read("|");
			Tc();
			buildTree("->", 3);
		}
}
void B(){
    Bt();
    while (token.value=="or") {
        read("or");
        Bt();
        buildTree("or", 2);
    }
}
void Bt(){
    Bs();
	while (token.value=="&") {
		read("&");
		Bs();
		buildTree("&", 2);
	}
}
void Bs(){
    if (token.value=="not") {
		read("not");
		Bp();
		buildTree("not", 1);
	}
	else {
		Bp();
	}
}
void Bp(){
    A();
    if ((token.value=="gr") || (token.value==">")) {
		read(token.value);
		A();
		buildTree("gr", 2);
    }
    else if ((token.value=="ge") || (token.value==">=")) {
		read(token.value);
		A();
		buildTree("ge", 2);
	}
    else if ((token.value=="ls") || (token.value=="<")) {
        read(token.value);
		A();
		buildTree("ls", 2);
    }
	else if (token.value=="le" || token.value=="<=") {
		read(token.value);
		A();
        buildTree("le", 2);
    }
	else if (token.value=="eq") {
		read("eq");
		A();
		buildTree("eq", 2);
    }
	else if (token.value=="ne") {
		read("ne");
		A();
        buildTree("ne", 2);
    }
}
void A(){
    if (token.value=="+") {
        read("+");
		At();
    }
    else if (token.value=="-") {
		read("-");
		At();
		buildTree("neg", 1);
	}
	else {
		At();
	}
	string temp;
	while ((token.value=="+") || (token.value=="-")) {
		temp = token.value;
		read(temp);
        At();
		buildTree(temp, 2);
    }
}
void At(){
    Af();
    string temp;
	while ((token.value=="*") || (token.value=="/")) {
		temp = token.value;
		read(temp);
		Af();
		buildTree(temp, 2);
	}
}
void Af(){
    Ap();
    if (token.value=="**") {
		read("**");
		Af();
		buildTree("**", 2);
	}
}
void Ap(){
    R();
    while (token.value=="@") {
		read("@");
		read(token.value);
		R();
		buildTree("@", 3);
	}
}
void R(){
    Rn();
    while ((std::find(keywords.begin(), keywords.end(), token.value) == keywords.end()) && (token.type=="IDENTIFIER"
                || token.type=="INTEGER" || token.type=="STRING" || token.value=="true"
                || token.value=="false" || token.value=="nil" || token.value=="(" || token.value=="dummy")) {
        Rn();
        buildTree("gamma", 2);
    }
}
void Rn(){
    if (token.type=="IDENTIFIER" || token.type=="INTEGER" || token.type=="STRING") {
        read(token.value);
    }
	else if (token.value=="true") {
		read("true");
		buildTree("true", 0);
	}
	else if (token.value=="false") {
		read("false");
		buildTree("false", 0);
    }
	else if (token.value=="nil") {
		read("nil");
		buildTree("nil", 0);
	}
	else if (token.value=="(") {
		read("(");
		E();
		read(")");
	}
	else if (token.value=="dummy") {
		read("dummy");
		buildTree("dummy", 0);
	}
}
void Da(){
    Dr();
	int n = 0;
	while (token.value=="and") {
		read("and");
		Dr();
		n++;
	}
	if (n > 0)
		buildTree("and", n+1);
}
void Dr(){
    if (token.value=="rec") {
        read("rec");
		Db();
		buildTree("rec", 1);
		}
    else
		Db();
}
void Db(){
    if (token.type=="IDENTIFIER") {
		Vl();
		if (token.value=="=") {
			read("=");
			E();
			buildTree("=", 2);
		}
		else {
            int n = 0;
			while (token.type=="IDENTIFIER" || token.value=="(") {
				Vb();
				n++;
			}
			read("=");
            E();
            buildTree("function_form", n+2);
        }
    }
    else if (token.value=="(") {
        read("(");
		D();
		read(")");
    }
}
void Vl(){
    if (token.type=="IDENTIFIER") {
        read(token.value);
    }
    int n = 0;
    while (token.value==",") {
        read(",");
        read(token.value);
        n++;
    }
    if (n > 0)
        buildTree(",", n+1);
}

