// Interpreter.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <ctype.h>

using namespace std;

class Token {

public:
    Token()
    {
        this->type = "EOF";
        this->text = "";
       
    }
    Token(string type, string text)
    {
        this->type = type;
        this->text = text;
    }
    string getType();
    string getText();
    void setType(string);
    void setText(string);
private:
    string type;
    string text;

};

string Token::getText()
{
    return this->text;
}

string Token::getType()
{
    return this->type;
}

void Token::setText(string text) {
    this->text = text;
}

void Token::setType(string type)
{
    this->type = type;
}

/*
    
    ->Fa modificari la cod astfel incat sa sare peste spatii albe
    ->Fa modificari ca in loc de + sa manipuleze si - sa evalueze si operatii ca 7 - 5
    

*/

class Interpreter {
  
public:
    Interpreter(string text)
    {
        this->text = text;
        this->pos = 0;
      
    }
    void error()
    {
        cout << "\nEROARE!!!\n\n";
        exit(0);

    }

    ///aceasta functie are ca si scop returnarea fiecarui element ca si un tuple de token name si token
    Token getNextToken()
    {
        Token currentToken;

        ///daca iesim din stringul current inseamna ca avem o eroare
        ///dar ce facem este ca returnam un token
        if (this->pos > text.size() - 1)
        {
            currentToken.setType("EOF");
            return currentToken;
        }

        ///aici luam caracterul current
        char currChar = this->text[this->pos];
        
        if (isspace(currChar))
        {
            while (isspace(currChar))
            {
                currChar = this->text[this->pos];
                this->pos++;
            }
            this->pos--;
        }
       
       
        ///daca caracterul current este un intreg
        ///caracterul curent il procesam ca si un integer
        ///iar daca nu caracterul il vom procesa ca si cand ar fi un semn de plus
        
        if (currChar >= '0' && currChar <= '9')
        {
            ///verificam daca nu cumva este format din mai multe cifre
            string auxInteger;
            auxInteger.push_back (currChar);
            this->pos++;
            while (isdigit(this->text[this->pos]))
            {
              
                auxInteger.push_back ( this->text[this->pos]);
                this->pos++;
            }
            currentToken.setText(auxInteger);
            currentToken.setType("INTEGER");
            
            return currentToken;
        }

        if (currChar == '+')
        {
            string aux;
            aux.push_back(currChar);
            currentToken.setText(aux);
            currentToken.setType("PLUS");
            this->pos++;
            if (this->sign == '.')
            {
                this->sign = '+';
            }
            else {
                this->error();
            }
            
            return currentToken;
            
        }
        if (currChar == '-')
        {
            string aux;
            aux.push_back(currChar);
            currentToken.setText(aux);
            currentToken.setType("PLUS");
            this->pos++;
            if (this->sign == '.')
            {
                this->sign = '-';
            }
            else {
                this->error();
            }

            return currentToken;

        }

        this->error();
    }


    void eat(string token_type)
    {
        if (this->currentToken.getType() != token_type)
            this->error();
        this->currentToken = this->getNextToken();
    }
    int expr()
    {
        this->currentToken = this->getNextToken();
        Token left = this->currentToken;
        ///ce face functia eat este ca verifica daca tokenul current este correct
        ///adica noi ne asteptam ca cel din stanga sa fie int si daca nu este int atunci facem urat
        this->eat("INTEGER");

        Token op = this->currentToken;
        ///apelam iara functia eat sa verificam daca tokenul current este cel bun si face ce trebuie
        ///anume daca este token care corespunde operatii de plus
        this->eat("PLUS");
        
        Token right = this->currentToken;
        this->eat("INTEGER");
        int result;
        if(this->sign == '+')
             result = stoi(left.getText())  + stoi(right.getText()) ;
        else if(this->sign == '-')
            result = stoi(left.getText()) - stoi(right.getText());
        else 
            this->error();
        return result;
    }


private:
    string text;
    int pos=0;
    Token currentToken;
    char sign = '.';

};

int main()
{
    string text;
    getline(cin, text);
    Interpreter t(text);
    int res = t.expr();
    cout <<  res << endl;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
