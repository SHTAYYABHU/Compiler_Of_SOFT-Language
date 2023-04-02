#include<iostream>
#include <cstring>
#include <string>
#include <iostream>
#include <ctype.h>
#include <fstream> 
#include <bits/stdc++.h>
#include <stdlib.h>
using namespace std;
string variable[250]
    = {};
int varsize=0;
char* char_code;
int line_leng,i;
string current_state="start";
string klist ="";
string variable_check="0";
string temp_variable,temp_value;
string error="";
string temp_error="";
string temp_op;
string temp_state="";



int start(char a) {
    if(a=='T') {
        current_state="h1";
    } else if(a=='B') {
        current_state="f1";
    } else if(a=='I') {
        current_state="i1";
    } else if(variable_check=="1") {
        current_state="setvariable";
        temp_variable=temp_variable+a;
    } else if(a=='D') {
        current_state="d1";
    } else if(a=='F') {
        current_state="ff1";
    }else if(a=='W'){
    current_state="w1";
    }else if(a=='R'){
    	current_state="r1";
	}else if(a=='S'){
		current_state="s1";
	}else{
		current_state=="ERROR";
	}
	    return 0;
}
int setvalue(char a) {
    if(a==';') {
        klist=klist+"numeric constant: "+temp_value+"\nterminator: ;\n";
        temp_value="";
        if(temp_state==""){
        	current_state="start";
		}else if(a>=48&&a<=57){
current_state="setvalue";
temp_value=temp_value+a;
			return 0;
		}else{
cout<<"error: semicolon missing";
return 0;
current_state="start";
		}
cout<<temp_state<<endl;
        return 0;
    }else{
    temp_value=temp_value+a;
    current_state="setvalue";

    return 0;
}}

int setvariable(char a) {
    if(a=='=') {
        klist=klist+"variable: "+temp_variable+"\n"+"operator: "+"="+"\n";
        current_state="setvalue";
        variable_check="0";
        variable[varsize]=temp_variable;
        varsize++;
        temp_variable="";
        return 0;
    } else if(a==';') {
        klist=klist+"variable: "+temp_variable+"\n"+"terminator: ;"+"\n";
        current_state="start";
        variable[varsize]=temp_variable;
        varsize++;
        temp_variable="";
        variable_check="0";
        return 0;
    }
    temp_variable=temp_variable+a;
    current_state="setvariable";
    return 0;
}

int ff1(char a) {
    if(a=='L') {
        current_state="ff2";
    }else if(a=='O'){
    current_state="fo2";
    }
    return 0;
}

int fo2(char a){
if(a=='R'){
klist=klist+"identifier: FOR\n";
current_state="fo3";
return 0;
}
return 0;}


int fo3(char a){
if(a=='<'){
current_state="fo4";
return 0;
}
return 0;
}

int fo4(char a){
if(a=='<'){
klist=klist+"opening bracket: <<\n";
current_state="fo5";
return 0;
}
return 0;
}

int fo5(char a){
//get variable

if((a>=65&&a<=90)||(a>=97&&a<=122)||(a>=48&&a<=57)){
temp_variable=temp_variable+a;
return 0;
}else if(a=='='){
int i;
for(i=0;i<varsize;i++){
if(temp_variable==variable[i]){
klist=klist+"variable: "+temp_variable+"\n"+"operator: =\n";
current_state="fo6";
temp_variable="";
return 0;
}else{
	temp_error="variable not defined: "+temp_variable;
}
}
error=error+temp_error;
return 0;
}
return 0;

}

int fo6(char a){
if(a>=48&&a<=57){
temp_value=temp_value+a;
current_state="fo6";
}else if(a==':'){
klist=klist+"numeric constant: "+temp_value+"\n"+"value divider: :\n";
temp_value="";
current_state="fo7";
return 0;
}
return 0;}

int fo7(char a){
if(a>=48&&a<=57){
temp_value=temp_value+a;
current_state="fo7";
}else if(a==';'){
klist=klist+"numeric constant: "+temp_value+"\n"+"value divider: ;\n";
temp_value="";
current_state="fo8";
}

return 0;
}

int fo8(char a){
if(a=='>'){
current_state="fo9";
}
return 0;
}

int fo9(char a){
if(a=='>'){
klist=klist+"closing bracket: >>\n";
current_state="fo10";
}
return 0;
}

int fo10(char a){
if(a=='('){
current_state="fo11";
klist=klist+"function bracket: (\n";
}
return 0;}

int fo11(char a){
if(a==')'){
current_state="start";
klist=klist+"function bracket: )\n";
}else{
current_state="start";
start(a);
}return 0;}

int ff2(char a) {
    if(a=='O') {
        current_state="ff3";
    }
    return 0;
}

int ff3(char a) {
    if(a=='A') {
        current_state="ff4";
    }
    return 0;
}

int ff4(char a) {
    if(a=='T') {
        current_state="ff5";
    }
    return 0;
}

int ff5() {
    klist=klist+"identifier: FLOAT"+"\n";
    current_state="setvariable";
    return 0;
}

int d1(char a) {
    if(a=='E') {
        current_state="d2";
    }
    return 0;
}

int d2(char a) {
    if(a=='C') {
        current_state="d3";
    }
    return 0;
}

int d3(char a) {
    if(a=='I') {
        current_state="d4";
    }
    return 0;
}

int d4(char a) {
    current_state="setvariable";
    klist=klist+"identifier: DECI"+"\n";
    return 0;
}
int i1(char a) {
    if(a=='N') {
        current_state="i2";
    }else if(a=='F'){
    	current_state="if1";
    	klist=klist+"identifier: IF\n";
	}
    return 0;
}

int i2(char a) {
    if(a=='T') {
        current_state="i3";
    }
    return 0;
}

int i3(char a) {
    current_state="setvariable";
    klist=klist+"identifier: INT"+"\n";
    return 0;
}

int f1(char a) {
    if(a=='O') {
        current_state="f2";
    }
    return 0;
}

int f2(char a) {
    if(a=='T') {
        current_state="f3";
    }
    return 0;
}

int f3(char a) {
    if(a=='T') {
        current_state="f4";
    }
    return 0;
}

int f4(char a) {
    if(a=='O') {
        current_state="f5";
    }
    return 0;
}

int f5(char a) {
    if(a=='M') {
        current_state="f6";
    }
    return 0;
}

int f6() {
    klist=klist+"footer: BOTTOM"+"\n";

    current_state="start";
    return 0;
}
int h1(char a) {
    if(a=='O') {
        current_state="h2";
    }
    return 0;
}

int h2(char a) {

    if(a=='P') {
        current_state="h3";
    }
    return 0;
}

int h3() {
    klist=klist+"header: TOP"+"\n";
    current_state="start";
    return 0;
}

int w1(char a){
if(a=='H'){
current_state="w2";
}else if(a=='R'){
current_state="wr1";
}else{
	error+error="undefined indentifier at line H\n";
}
return 0;}

int w2(char a){
if(a=='I'){
current_state="w3";
}else{
	error=error+"undefined indentifier at line I\n";
}
return 0;}

int w3(char a){
if(a=='L'){
current_state="w4";
}else{
	error=error+"undefined indentifier at line L\n";
}
return 0;}


int w4(char a){
if(a=='E'){
current_state="w5";
klist=klist+"identifier: WHILE\n";
}else if(!(a=='E')){
	return 0; 
}
return 0;}

int w5(char a){
if(a=='<'){
current_state="w6";
}
return 0;}

int w6(char a){
if(a=='<'){
current_state="w7";
klist=klist+"opening bracket: <<\n";
}
return 0;}

int w9(char a){
	if(a>=48&&a<=57){
temp_value=temp_value+a;
		return 0;
	}else if(a=='>'){
		klist=klist+"numeric constant: "+temp_value+"\n";
		temp_value="";
		current_state="w10";
return 0;
	}	
	return 0;
}

int w10(char a){
	if(a=='>'){
		klist=klist+"closing bracket: >>\n";
		current_state="w11";
	}
	return 0;
}
int w11(char a){
	if(a=='('){
		current_state="w12";
	klist=klist+"opening function bracket: (\n";
	}
	return 0;
}
int w12(char a){
if(a==')'){
	klist=klist+"closing function bracket: )\n";
}else{
current_state="start";
temp_state="w12";
cout<<a<<temp_state<<endl ;
start(a);
return 0;
}
	return 0;

}
int w8(char a){

	if(a>=48&&a<=57){
		current_state="w9";
klist=klist+"operator: "+temp_op+"\n";
w9(a);
temp_op="";
		return 0;
	}
	temp_op=temp_op+a;
	current_state="w8";
	return 0;
}

int w7(char a){
if((a>=65&&a<=90)||(a>=97&&a<=122)||(a>=48&&a<=57)){
temp_variable=temp_variable+a;
//cout<<temp_variable<<endl;
return 0;
}else if(a=='!'||a=='>'||a=='<'||a=='='){
current_state="w8";
int i;
for(i=0;i<varsize;i++){
	if(temp_variable==variable[i]){
klist=klist+"variable: "+temp_variable+"\n";
temp_variable=""; 
w8(a);
}else{
	cout<<"undefined variable\n";
}
}return 0;
}
return 0;
}

int r1(char a){
	if(a=='E'){
		current_state="r2";
	}
	return 0;
}
int r2(char a){
	if(a=='A'){
		current_state="r3";
	}
	return 0;
}
int r3(char a){
	if(a=='D'){
		current_state="r4";
	klist=klist+"identifier: READ\n";
	}
	return 0;
}
int r4(char a){
if(a=='<'){
current_state="r5";
}
	return 0;
}

int r5(char a){
	if(a=='<'){
current_state="r6";
klist=klist+"opening bracket: <<\n";
}
	return 0;
}
int r6(char a){
int i;
if(a=='>'){
for(i=0;i<varsize;i++){
	if(temp_variable==variable[i]){
		klist=klist+"variable: "+temp_variable+"\n";
		temp_variable="";
		current_state="r7";
	}
}

}else{
	if((a>=97&&a<=122)||(a>=65&&a<=90)||(a>=48&&a<=57)){
		temp_variable=temp_variable+a;
		return 0;
	}
	
}	return 0;
}
int r7(char a){
if(a=='>'){
	current_state="start";
	klist=klist+"closing bracket: >>\n";
}
	return 0;
}

int wr1(char a){
if(a=='I'){
current_state="wr2";
}
return 0;
}

int wr2(char a){
if(a=='T'){
current_state="wr3";
}
return 0;
}

int wr3(char a){
if(a=='E'){
current_state="wr4";
klist=klist+"identifier: WRITE\n";
}
return 0;
}
int wr4(char a){
if(a=='<'){
current_state="wr5";
}
return 0;
}

int wr5(char a){
if(a=='<'){
current_state="wr6";
klist=klist+"opening bracket: <<\n";
}
return 0;
}
int wr10(char a){
if(a=='\''){
current_state="wr7";
klist=klist+"string quotation mark: \'\n";
}else{
error="invalid operator in WRITE: +";}
return 0;}

int wr6(char a){

if(a=='\''){
current_state="wr7";
klist=klist+"string quotation mark: \'\n";
}else if(a=='+'){
int i;
for(i=0;i<varsize;i++){
if(temp_variable==variable[i]){
klist=klist+"variable value in WRITE: "+temp_variable+"\n";
}else{
error="invalid variable in WRITE: "+temp_variable;
return 1;
}
}
current_state="wr10";
klist=klist+"WRITE divider: +\n";
}else{
temp_variable=temp_variable+a;
}
return 0;
}
int wr7(char a){

if(a=='\''){
current_state="wr8";
klist=klist+"WRITE string: "+temp_value+"\nstring close quotation marks: \'\n";
temp_value="";
}else{
temp_value=temp_value+a;
}
return 0;
}

int wr8(char a){
cout<<a;
if(a=='>'){
current_state="wr9";
}else if(a=='+'){
klist=klist+"divider: +\n";
current_state="wr11";
}
return 0;
}
int wr11(char a){
if(a=='>'){
int i;
for(i=0;i<varsize;i++){
if(temp_variable==variable[i]){
klist=klist+"variable: "+temp_variable+"\n";
temp_variable="";
current_state="wr9";
}
}
return 0;
}else if(a=='+'){
current_state="w11";
klist=klist+"divider: +\n";
}else{
temp_variable=temp_variable+a;
}
return 0;}
int wr9(char a){
if(a=='>'){
	if(temp_state==""){
current_state="start";}else{
	current_state=temp_state;
}
klist=klist+"closing bracket: >>\n";
}
return 0;
}

int if1(char a){
if(a=='<'){
	current_state="if2";
}
	return 0;
}

int if2(char a){
	if(a=='<'){
		current_state="if3";
	klist=klist+"opening bracket <<\n";
	}
	return 0;
}
int if5(char a){
	temp_op="";
	temp_variable="";
	if(a>=48&&a<=57){
		temp_value=temp_value+a;
		current_state="if5";
	}else if(a=='>'){
		current_state="if6";
		klist=klist+"numeric constant: "+temp_value+"\n";
		temp_value="";
	}
	return 0;
}
int if6(char a){
	if(a=='>'){
		klist=klist+"closing bracket >>\n";
		current_state="if7";
	}
}
int if7(char a){
	if(a=='('){
		current_state="if8";
		klist=klist+"opening function bracket: (\n";
	}
return 0;
}
int if8(char a){
if(a==')'){
	klist=klist+"closing function bracket4: "+a+"\n";
	current_state="if9";
	return 0;
}else{
	current_state="start";
	temp_state="if8";
	start(a);
	
}	
return 0;
}
int if9(char a){
	if(a=='E'){
		current_state="if10";
	}else{
		current_state="start";
		start(a);
	}
	return 0;
}
int if10(char a){
if(a=='L'){
	current_state="if11";
}
	return 0;
}

int if11(char a){
if(a=='S'){
	current_state="if12";
}
	return 0;
}

int if12(char a){
if(a=='E'){
	current_state="if13";
	klist=klist+"indentifier: ELSE\n";
}
	return 0;
}

int if13(char a){
	if(a=='('){
		current_state="if14";
		klist=klist+"opening function bracket: (\n";
	}else if(a=='I'){
		current_state="if15";
	}
	return 0;
}
int if15(char a){
	if(a=='F'){
		current_state="if1";
	}
	return 0;
}
int if14(char a){
	cout<<a;
	if(a==')'){
		current_state="start";
	klist=klist+"closing function bracket4: )\n";
	}else
	{
		current_state="start";
	}
}
int if4(char a){
if((a=='!')||(a=='<')||(a=='>')||(a=='=')){
temp_op=temp_op+a;
current_state="if4";
}else if(a>=48&&a<=57){
	current_state="if5";
	klist=klist+"operator: "+temp_op+"\n";
	if5(a);
}
	return 0;
}

int if3(char a){
//get variable
if(!(a>=97&&a<=122)||(a>=65&&a<=90)||(a>=48&&a<=57)){
klist=klist+"variable: "+temp_variable+"\n";
current_state="if4";
if4(a);
}else if((a>=97&&a<=122)||(a>=65&&a<=90)||(a>=48&&a<=57)){
	temp_variable=temp_variable+a;
}
	return 0;
}

int s1(char a){
if(a=='W'){
	current_state="s2";
}
	return 0;
}
int s2(char a){
if(a=='I'){
	current_state="s3";
}
	return 0;
}
int s3(char a){
if(a=='T'){
	current_state="s4";
}
	return 0;
}
int s4(char a){
if(a=='C'){
	current_state="s5";
}
	return 0;
}
int s5(char a){
if(a=='H'){
	klist=klist+"identifier: SWITCH\n";
	current_state="s6";
}
	return 0;
}
int s6(char a){
if(a=='<'){
	current_state="s7";
}
	return 0;
}
int s7(char a){
if(a=='<'){
	klist=klist+"opening bracket: <<\n";
	current_state="s8";
}
	return 0;
}
int s8(char a){
if((a>=65&&a<=90)||(a>=97&&a<=122)||(a>=48&&a<=57)){
temp_variable=temp_variable+a;
//cout<<temp_variable<<endl;
return 0;
}else if(a=='>'){
	int i;
	for(i=0;i<varsize;i++){
		if(temp_variable==variable[i]){
			klist=klist+"variable: "+temp_variable+"\n";
			temp_variable="";
			current_state="s9";
		temp_error="";
			return 0;
		
		}else{
			temp_error="invalid variable\n";
		}
	}
error=error+temp_error;
}
return 0;
}
int s9(char a){
if(a=='>'){
	current_state="s10";
klist=klist+"closing bracket: >>\n";
}
	return 0;
}
int s10(char a){
if(a=='('){
klist=klist+"opening function bracket: (\n";
	current_state="s11";
}
	return 0;
}
int s11(char a){
if(a=='C'){
	klist=klist+"SWITCH identifier: C\n";
	current_state="s12";
}
	return 0;
}
int s12(char a){
if(a=='<'){
	current_state="s13";
}
	return 0;
}
int s13(char a){
if(a=='<'){
	klist=klist+"opening bracket: <<\n";
	current_state="s14";
}
	return 0;
}
int s14(char a){
if((a>=65&&a<=90)||(a>=97&&a<=122)||(a>=48&&a<=57)){
	temp_value=temp_value+a;
}else if(a=='>'){
	current_state="s15";
}
	return 0;
}int s15(char a){
if(a=='>'){
	klist=klist+"C value: "+temp_value+"\nclosing bracket: >>\n";
temp_value="";
	current_state="s16";
}
	return 0;
}
int s16(char a){
if(a=='('){
	klist=klist+"opening function bracket: (\n";
	current_state="s17";
}
	return 0;
}
int s17(char a){
	cout<<a;
if(a=='S'){
	current_state="s18";
}else{
	current_state="start";
	start(a);
temp_state="s17";
}
	return 0;
}
int s18(char a){
if(a=='E'){
	current_state="s19";
}
	return 0;
}int s19(char a){
if(a=='T'){
	current_state="s20";
}
	return 0;
}int s20(char a){
if(a==')'){
	klist=klist+"closing function bracket: )\n";
	current_state="s21";
}
	return 0;
}
int s21(char a){
	if(a=='R'){
		current_state="s22";
	}else if(a=='C'){
			klist=klist+"SWITCH identifier: C\n";
		current_state="s12";
	}
	return 0;
}
int s22(char a){
	if(a=='E'){
		current_state="s23";
	}
	return 0;
}
int s23(char a){
	if(a=='S'){
		current_state="s24";
	}
	return 0;
}
int s24(char a){
	if(a=='E'){
		current_state="s25";
	}
	return 0;
}
int s25(char a){
	if(a=='T'){
		klist=klist+"method: RESET\n";
		current_state="s26";
	}
	return 0;
}
int s26(char a){
	if(a=='('){
		klist=klist+"opening bracket: (\n";
		current_state="s27";
	}
	return 0;
}
int s27(char a){
	if(a==')'){
		klist=klist+"opening bracket: )\n";		
if(temp_state==""){
	current_state="start";
	temp_state="";
}else{
	current_state=temp_state;
}	}else{
		current_state="start";
		temp_state="s27";
	}
}

int isaccept() {
    for(i=0; i<=line_leng; i++) {
        if(current_state=="start") {
            start(char_code[i]);
        }else if(char_code[i]==' '){
		} else if(current_state=="h1") {
            h1(char_code[i]);
        } else if(current_state=="h2") {
            h2(char_code[i]);
        } else if(current_state=="h3") {
            h3();
            i--;
        } else if(current_state=="f1") {
            f1(char_code[i]);
        } else if(current_state=="f2") {
            f2(char_code[i]);
        } else if(current_state=="f3") {
            f3(char_code[i]);
        } else if(current_state=="f4") {
            f4(char_code[i]);
        } else if(current_state=="f5") {
            f5(char_code[i]);
        } else if(current_state=="f6") {
            f6();
        } else if(current_state=="i1") {
            i1(char_code[i]);
        } else if(current_state=="i2") {
            i2(char_code[i]);
        } else if(current_state=="i3") {
            i3(char_code[i]);
            i--;
        } else if(current_state=="d2") {
            d2(char_code[i]);
        } else if(current_state=="d3") {
            d3(char_code[i]);
        } else if(current_state=="d4") {
            d4(char_code[i]);
            i--;
        } else if(current_state=="ff1") {
            ff1(char_code[i]);
        } else if(current_state=="ff2") {
            ff2(char_code[i]);
        } else if(current_state=="ff3") {
            ff3(char_code[i]);
        } else if(current_state=="ff4") {
            ff4(char_code[i]);
        } else if(current_state=="ff5") {
            ff5();
            i--;
        }
        else if(current_state=="setvariable") {
            setvariable(char_code[i]);
        } else if(current_state=="setvalue") {
            setvalue(char_code[i]);
        } else if(current_state=="d1") {
            d1(char_code[i]);
        }else if(current_state=="fo2"){
        fo2(char_code[i]);
        }else if(current_state=="fo3"){
        fo3(char_code[i]);
        }else if(current_state=="fo4"){
        fo4(char_code[i]);
        }else if(current_state=="fo5"){
        fo5(char_code[i]);
        }else if(current_state=="fo6"){
        fo6(char_code[i]);
        }else if(current_state=="fo7"){
        fo7(char_code[i]);
        }else if(current_state=="fo8"){
        fo8(char_code[i]);
        }else if(current_state=="fo9"){
        fo9(char_code[i]);
        }else if(current_state=="fo10"){
        fo10(char_code[i]);
        }else if(current_state=="fo11"){
        fo11(char_code[i]);
        }else if(current_state=="w1"){
        w1(char_code[i]);
        }else if(current_state=="w2"){
        w2(char_code[i]);
        }else if(current_state=="w3"){
        w3(char_code[i]);
        }else if(current_state=="w4"){
        w4(char_code[i]);
        }else if(current_state=="w5"){
        w5(char_code[i]);
        }else if(current_state=="w6"){
        w6(char_code[i]);	
		}else if(current_state=="w7"){
			w7(char_code[i]);
		}else if(current_state=="w8"){
			w8(char_code[i]);
		}else if(current_state=="w9"){
			w9(char_code[i]);
		}else if(current_state=="w10"){
			w10(char_code[i]);
		}else if(current_state=="w11"){
			w11(char_code[i]);
		}else if(current_state=="w12"){
//	cout<<char_code[i]<<endl;
			w12(char_code[i]);
		}else if(current_state=="r1"){
			r1(char_code[i]);
		}else if(current_state=="r2"){
			r2(char_code[i]);
		}else if(current_state=="r3"){
			r3(char_code[i]);
		}else if(current_state=="r4"){
			r4(char_code[i]);
		}else if(current_state=="r5"){
			r5(char_code[i]);
		}else if(current_state=="r6"){
			r6(char_code[i]);
		}else if(current_state=="r7"){
			r7(char_code[i]);
		}else if(current_state=="wr1"){
wr1(char_code[i]);
}else if(current_state=="wr2"){
wr2(char_code[i]);
}else if(current_state=="wr3"){
wr3(char_code[i]);
}else if(current_state=="wr4"){
wr4(char_code[i]);
}else if(current_state=="wr5"){
wr5(char_code[i]);
}else if(current_state=="wr6"){
wr6(char_code[i]);
}else if(current_state=="wr7"){
wr7(char_code[i]);
}else if(current_state=="wr8"){
wr8(char_code[i]);
}else if(current_state=="wr9"){
wr9(char_code[i]);
}else if(current_state=="w10"){
w10(char_code[i]);
}else if(current_state=="wr11"){
wr11(char_code[i]);
}else if(current_state=="if1"){
	if1(char_code[i]);
}else if(current_state=="if2"){
	if2(char_code[i]);
}else if(current_state=="if3"){
	if3(char_code[i]);
}else if(current_state=="if4"){
	if4(char_code[i]);
}else if(current_state=="if5"){
	if5(char_code[i]);
}else if(current_state=="if6"){
	if6(char_code[i]);
}else if(current_state=="if7"){
	if7(char_code[i]);
}else if(current_state=="if8"){
	if8(char_code[i]);
}else if(current_state=="if9"){
	if9(char_code[i]);
}else if(current_state=="if10"){
	if10(char_code[i]);
}else if(current_state=="if11"){
	if11(char_code[i]);
}else if(current_state=="if12"){
	if12(char_code[i]);
}else if(current_state=="if13"){
	if13(char_code[i]);
}else if(current_state=="if14"){
	if14(char_code[i]);
}else if (current_state=="if15"){
	if15(char_code[i]);
}else if(current_state=="s1"){
	s1(char_code[i]);
}else if(current_state=="s2"){
	s2(char_code[i]);
}else if(current_state=="s3"){
	s3(char_code[i]);
}else if(current_state=="s4"){
	s4(char_code[i]);
}else if(current_state=="s5"){
	s5(char_code[i]);
}else if(current_state=="s6"){
	s6(char_code[i]);
}else if(current_state=="s7"){
	s7(char_code[i]);
}else if(current_state=="s8"){
	s8(char_code[i]);
}else if(current_state=="s9"){
	s9(char_code[i]);
}else if(current_state=="s10"){
	s10(char_code[i]);
}else if(current_state=="s11"){
	s11(char_code[i]);
}else if(current_state=="s12"){
	s12(char_code[i]);
}else if(current_state=="s13"){
	s13(char_code[i]);
}else if(current_state=="s14"){
	s14(char_code[i]);
}else if (current_state=="s15"){
	s15(char_code[i]);
}else if (current_state=="s16"){
	s16(char_code[i]);
}else if (current_state=="s17"){
	s17(char_code[i]);
}else if (current_state=="s18"){
	s18(char_code[i]);
}else if (current_state=="s19"){
	s19(char_code[i]);
}else if (current_state=="s20"){
	s20(char_code[i]);
}else if (current_state=="s21"){
	s21(char_code[i]);
}else if (current_state=="s22"){
	s22(char_code[i]);
}else if (current_state=="s23"){
	s23(char_code[i]);
}else if (current_state=="s24"){
	s24(char_code[i]);
}else if (current_state=="s25"){
	s25(char_code[i]);
}else if (current_state=="s26"){
	s26(char_code[i]);
}else if (current_state=="s27"){
	s27(char_code[i]);
}else if(current_state=="ERROR"){
	return 15;
}
    }
    return 0;
}
int convert_toArray(string line) {
    line_leng=line.length();
    char_code = new char[line_leng + 1];

    strcpy(char_code, line.c_str());

int check=isaccept();
if(check==15){
	cout<<"error in code";
	exit(0);
}
    return 0;

}

int main()
{
	ifstream code; 
	code.open("code.SOFT");
string codeline;
do{
getline (code, codeline);
convert_toArray(codeline);
}while(code);
if(error==""){

cout<<klist;
}else{
cout<<error;
}return 0;
}
