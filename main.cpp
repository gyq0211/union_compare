#include <iostream>
#include <malloc.h>
#include <string>
#include<list>
#include<vector>
#include <string.h>
using namespace std;


/*split string array*/
//original: the initial string
//num: the length to split
vector<string> split_string(string original,int num)
{
    int len=original.length();
    int end=num;
    string s;
    std::vector<string> list1;
    for(int start=0;start<len;)
    {
        /*if the last part is shorter than num, fill it up with 0*/
        if(end>len)
        {
            //s=original.substr(start,len-start);//the last part
            //s.append(end-len,'0');//append 0 in
            //cout<<s<<endl;
            cout<<"The expression is invalid!"<<endl;
            break;
        }
        /*starting from 0, split the string*/
        s=original.substr(start,num);
        start=end;
        end=end+num;
        list1.push_back(s);
        //cout<<s<<endl;
    }
    return list1;
}

/*Definition for unit_compare struct array*/
struct Compare
{
    bool op_left;
    bool op_right;
    string op_type;
    string logic_type;//The logical comparator before one unit_compare
};

int main()
{
    /*user input*/
    cout<<"Please enter the logical expression"<<endl;
    string s;
    cin>>s;
    //unsigned int len_s = sizeof(s)/sizeof(s[0]);
    /*if ((len_s <= 5) ||(((len_s+2)%5)!=0))
    {
        cout<<"The expression is invalid"<<endl;
        //break;
    }*/
    vector<string> split_s = split_string(s,1);
    unsigned int num_compare = ((s.length()+2)/5);//num of struct
    cout<<"num_compare:"<<num_compare<<endl;
    Compare compare[num_compare];
    for (unsigned int i=0;i<(num_compare);i++)
    {
        if(i==0)
        {
            if (split_s[i] == "0")
            {
                compare[i].op_left = 0;
            }
            else
            {
                compare[i].op_left = 1;
            }

            if (split_s[i+2] == "0")
            {
                compare[i].op_right = 0;
            }
            else
            {
                compare[i].op_right = 1;
            }
            compare[i].op_type = split_s[i+1];
            compare[i].logic_type = "";
        }
        else
        {
            if (split_s[5*i] == "0")
            {
                compare[i].op_left = 0;
            }
            else
            {
                compare[i].op_left = 1;
            }

            if (split_s[5*i+2] == "0")
            {
                compare[i].op_right = 0;
            }
            else
            {
                compare[i].op_right = 1;
            }
            compare[i].op_type = split_s[5*i+1];
            compare[i].logic_type = split_s[5*i-2]+split_s[5*i-1];
        }
    }
    for (unsigned int i=0;i<(num_compare);i++)
    {
        cout<<"Split the process of unit_compare:"<<endl;
        cout<<compare[i].op_left<<endl;
        cout<<compare[i].op_type<<endl;
        cout<<compare[i].op_right<<endl;
        cout<<compare[i].logic_type<<endl;
    }
    cout << "The process of unit_compare is:" << endl;
    int result = 0;
    /*Instantiation for 5 unit_compare*/
    //Compare compare[] = {{0,0,"=",""},{0,0,">","||"},{1,0,"=","&&"},{1,0,">","||"},{1,0,"<","&&"}};
    /*Compute num of struct*/
    //unsigned int num_compare = sizeof(compare)/sizeof(compare[0]);
    /*Store the result for the unit_compare*/
    bool temp[num_compare] = {};
    /*unit_compare loop*/
    for (unsigned int i=0;i<num_compare;i++)
    {
        if(compare[i].op_type == ">")
        {
            temp[i] = (compare[i].op_left > compare[i].op_right);
            cout<<compare[i].op_left<<">"<<compare[i].op_right<<"is "<<temp[i]<<endl;
        }
        if(compare[i].op_type == "<")
        {
            temp[i] = (compare[i].op_left < compare[i].op_right);
            cout<<compare[i].op_left<<"<"<<compare[i].op_right<<"is "<<temp[i]<<endl;
        }
        if(compare[i].op_type == "=")
        {
            temp[i] = (compare[i].op_left == compare[i].op_right);
            cout<<compare[i].op_left<<"="<<compare[i].op_right<<"is "<<temp[i]<<endl;
        }
    }
    cout<<"Finished unit_compare, temp is: "<<endl;
    for (unsigned int i=0;i<num_compare;i++)
    {
        cout<<temp[i];
    }
    cout<<endl;
    cout<<"Process for logic_compare"<<endl;

    /*logic_compare loop*/
    std::vector<bool> list_or;
    bool CompareLast;//store value of AND temporarily
    bool CompareTemp[num_compare];
    memcpy(CompareTemp,temp,sizeof(CompareTemp));//copy value of temp to CompareLast
    list<bool> resultList(10);

    for (unsigned int i=0;i<num_compare;i++)
    {
        if(i==0)
        {
            CompareLast = CompareTemp[i];
            cout<<"When i=0 ,CompareLast is :"<<CompareLast<<endl;
        }
        else
        {
            if((compare[i].logic_type == "&&")&&(i != 0))
            {
                //CompareLast = (temp[i] && temp[i+1]);//if AND, compute last
                CompareLast = CompareLast && CompareTemp[i];//if AND, compute last
                cout<<"When i="<<i<<" ,CompareLast for && is :"<<CompareLast<<endl;
            }
            if((compare[i].logic_type == "||")&&(i != 0))
            //else
            {
                list_or.push_back(CompareLast);
                CompareLast = CompareTemp[i];
                //unsigned int len_list_or = sizeof(list_or)/sizeof(list_or[0]);
                unsigned int len_list_or = list_or.size();
                for(unsigned int j=0;j<len_list_or;j++)
                {
                    cout<<"When j="<<j<<" ,list for || is :"<<list_or[j]<<endl;
                }
            }
        }
    }
    /*do OR for all eles*/
    list_or.push_back(CompareLast);
    //unsigned int num_logic_com = sizeof(list_or)/sizeof(list_or[0]);
    unsigned int num_logic_com = list_or.size();
    for(unsigned int i=0;i<num_logic_com;i++)
    {
        result = result||list_or[i];
    }
    cout<<"The result is:"<<result<<endl;
    /*check result. If user input, compute the result by yourself*/
    /*bool check_result = ((0==0)||(0>0)&&(1==0)||(1>0)&&(1<0));
    cout<<"Checking result:"<<check_result<<endl;
    if(result==check_result)
    {
        cout<<"Successful!"<<endl;
    }*/
    /*The following lines are for testing example.*/
    //0=0&&0=0&&0=0
    //1=0&&1=0&&1=0||1=0
    return 0;
}
