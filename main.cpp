#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <vector>
#include <cstring>
#include <fstream>
#include "kmap.cpp"
using namespace std;

int findIndex(const vector<string> &arr, string item) {

    for (auto i = 0; i < arr.size(); ++i) {
        if (arr[i] == item)
            return i;
    }

    return -1;
}


int main(int argc,char *argv[])
{
    vector<string> variable_present,variable_in,variable_next,variable_out;
    vector<string> present_stt,input,next_stt,output;
    //input_for_kmap(argv,variable_present,variable_in,variable_next,variable_out,present_stt,input,next_stt,output);
    /////////--------------stage 1----------/////////////////////////
    string ff,temp_string,temp_str;//flip-flop-type
    //char temp[1];
    string temp_get;

    //cout << "Please enter the name of the input file: ";
    ifstream intruth(argv[1],ios::in);
    //cout << "Loading the file..."<<endl;
    intruth.seekg(10);
    intruth>>ff;//////choose flip-flop
    //cout <<ff;
    intruth>>temp_string;////get present whole
    for(int i = 10;i<temp_string.length();i++)//get present variable
    {
        if(temp_string[i] == ',')
            continue;
        if(temp_string[i] == ')')
            break;
        temp_str = temp_string[i];
        variable_present.push_back(temp_str);
    }
    /*for (int i = 0;i < variable_present.size();i++)
    {
        cout << "i: "<<i<<variable_present[i]<<endl;
    }*/
    for (int i = 0;i<64;i++)/////present state truth
    {
        intruth >> temp_string;
        if(temp_string.length() > 1)
        {
            for(int j = 8;j<temp_string.length();j++)//get input variable
            {
                if(temp_string[j] == ',')
                    continue;
                if(temp_string[j] == ')')
                    break;
                temp_str = temp_string[j];
                variable_in.push_back(temp_str);
            }
            //cout <<"safffffffffffff"<<endl;

            //item.push_back(temp_string);
            break;
        }
        //cout <<"temp: "<<temp<<endl;
        temp_get = temp_string;
        present_stt.push_back(temp_get);
    }
    //////////////////---------------------
    for (int i = 0;i<64;i++)////input
    {
        intruth >> temp_string;
        //cout <<"temp_str: "<<temp_str<<endl;
        if(temp_string.length() > 1)
        {
            for(int j = 7;j<temp_string.length();j++)//get next variable
            {
                if(temp_string[j] == ',')
                    continue;
                if(temp_string[j] == ')')
                    break;
                temp_str = temp_string[j];
                //cout <<"*******************temp_str: "<<temp_str<<endl;
                variable_next.push_back(temp_str);
            }
            //cout <<"yyyyyyyyyyyyyyy"<<endl;
            //item.push_back(temp_string);
            break;
        }
        //cout <<"XXXXXXXXXXXXXXXXXXXXXX"<<endl;
        //cout << "temp_get: "<<temp_string<<endl;
        temp_get = temp_string;
        input.push_back(temp_get);
    }
    /////////////////------------------------
    for (int i = 0;i<64;i++)/////next state
    {
        intruth >> temp_string;
        if(temp_string.length() > 1)
        {
            for(int j = 9;j<temp_string.length();j++)//get output variable
            {
                if(temp_string[j] == ',')
                    continue;
                if(temp_string[j] == ')' /*|| temp_string[j] == '0'*/)
                    break;
                temp_str = temp_string[j];
                variable_out.push_back(temp_str);
            }
            //cout <<"sdddddddddddd"<<endl;
            //item.push_back(temp_string);
            break;
        }
        temp_get = temp_string;
        next_stt.push_back(temp_get);
    }
    /////////////////------------------------
    for (int i = 0;i<64;i++)////output use input size to decide ow long it should take
    {
        if(temp_str[0] == '0'||i==input.size())
        {
             break;
        }
        //cout <<"i: "<<i<<" "<<temp_string<<endl;
        intruth >> temp_string;
        temp_get = temp_string;
        //cout << "stoi: "<<temp_get<<endl;
        output.push_back(temp_get);
    }
    /////////////////------------------------
    if(variable_next.size() == 1)//1 next variable
    {
        /*if(next_stt.size()==4)//no change
        {
            break;
        }*/
        if(next_stt.size()==8)
        {
            swap(next_stt[2],next_stt[3]);
            swap(next_stt[6],next_stt[7]);
            //cout <<"done for size 888888888888888888888888"<<endl;
        }
        else if(next_stt.size()==16)
        {
            for(int j = 0 ;j < 4;j++)//change vertical
            {
                swap(next_stt[j+2+3*j],next_stt[j+3+3*j]);
                //cout << "done swap!!!!!!!!"<<endl;
            }
            for(int k = 0 ;k < 4;k++)//change horizontal
            {
                swap(next_stt[k+8],next_stt[k+12]);
                //cout << "done swap!!!!!!!!"<<endl;
            }
        }
    }
    else if(variable_next.size() == 2)//2 next variable
    {
        /*if(next_stt.size()==8)//each variable 4 elements
        {
            swap(next_stt[1],next_stt[2]);
            swap(next_stt[6],next_stt[7]);
            cout <<"done for size 8"<<endl;
        }*/
        if(next_stt.size()==16)//each variable 8 elements
        {
            swap(next_stt[4],next_stt[6]);//A
            swap(next_stt[12],next_stt[14]);//A
            swap(next_stt[5],next_stt[7]);//B
            swap(next_stt[13],next_stt[15]);//B
            //cout <<"swap done for 2 next variables"<<endl;
        }
        else if(next_stt.size()==32)//each variable 16 elements
        {
            for(int i = 0;i<variable_next.size();i++)//2 next variable
            {
                for(int j = 0 ;j < 4;j++)//change vertical
                {
                    swap(next_stt[j+4+7*j+i],next_stt[j+6+7*j+i]);
                    //cout << "done swap!!!!!!!!"<<endl;
                }
                for(int k = 0 ;k < 4;k++)//change horizontal
                {
                    swap(next_stt[16+2*k+i],next_stt[24+2*k+i]);
                    //cout << "done swap!!!!!!!!"<<endl;
                }
            }

            //cout <<"swap done for 2 next variables"<<endl;
        }
    }
    else if(variable_next.size() == 3)//3 next variable
    {
        if(next_stt.size()==24)//each variable 8 elements
        {
            for(int i = 0;i<variable_next.size();i++)
            {
                swap(next_stt[6+i],next_stt[6+i+3]);
                swap(next_stt[18+i],next_stt[18+i+3]);
            }
        }
        else if(next_stt.size()==48)//each variable 8 elements
        {
            for(int i = 0;i<variable_next.size();i++)
            {
                for (int j = 0;j<4;j++)//change vertical
                {
                    swap(next_stt[i+6+12*j],next_stt[i+6+12*j+3]);
                }
                for(int k = 0 ;k < 4;k++)//change horizontal
                {
                    swap(next_stt[i+24+3*k],next_stt[i+24+3*k+12]);
                }
                //cout << "done swap!!!!!!!!"<<endl;
            }
        }
    }
    ////////////////----------------------------
    if(variable_out.size() == 1)//1 next variable
    {
        /*if(next_stt.size()==4)//no change
        {
            break;
        }*/
        if(output.size()==8)
        {
            swap(output[2],output[3]);
            swap(output[6],output[7]);
            //cout <<"done for size 7777777777777777777"<<endl;
        }
        else if(output.size()==16)
        {
            for(int j = 0 ;j < 4;j++)//change vertical
            {
                swap(output[j+2+3*j],output[j+3+3*j]);
                //cout << "done swap!!!!!!!!"<<endl;
            }
            for(int k = 0 ;k < 4;k++)//change horizontal
            {
                swap(output[k+8],output[k+12]);
                //cout << "done swap!!!!!!!!"<<endl;
            }
        }
    }
    else if(variable_out.size() == 2)//2 next variable
    {
        /*if(next_stt.size()==8)//each variable 4 elements
        {
            swap(next_stt[1],next_stt[2]);
            swap(next_stt[6],next_stt[7]);
            cout <<"done for size 8"<<endl;
        }*/
        if(output.size()==16)//each variable 8 elements
        {
            swap(output[4],output[6]);//A
            swap(output[12],output[14]);//A
            swap(output[5],output[7]);//B
            swap(output[13],output[15]);//B
            //cout <<"swap done for 2 out variables"<<endl;
        }
        else if(output.size()==32)//each variable 16 elements
        {
            for(int i = 0;i<variable_out.size();i++)//2 next variable
            {
                for(int j = 0 ;j < 4;j++)//change vertical
                {
                    swap(output[j+4+7*j+i],output[j+6+7*j+i]);
                    //cout << "done swap!!!!!!!!"<<endl;
                }
                for(int k = 0 ;k < 4;k++)//change horizontal
                {
                    swap(output[16+2*k+i],output[24+2*k+i]);
                    //cout << "done swap!!!!!!!!"<<endl;
                }
            }

            //cout <<"swap done for 2 out variables"<<endl;
        }
    }
    else if(variable_out.size() == 3)//3 next variable
    {
        if(output.size()==24)//each variable 8 elements
        {
            for(int i = 0;i<variable_out.size();i++)
            {
                swap(output[6+i],output[6+i+3]);
                swap(output[18+i],output[18+i+3]);
            }
        }
        else if(output.size()==48)//each variable 8 elements
        {
            for(int i = 0;i<variable_out.size();i++)
            {
                for (int j = 0;j<4;j++)//change vertical
                {
                    swap(output[i+6+12*j],output[i+6+12*j+3]);
                }
                for(int k = 0 ;k < 4;k++)//change horizontal
                {
                    swap(output[i+24+3*k],output[i+24+3*k+12]);
                }
                //cout << "done swap    out!!!!!!!!"<<endl;
            }
        }
    }
    ////////////////----------------------------
    ofstream outkmap("kmap_in.txt",ios::out);
    if(!outkmap)
    {
        cerr << "k_map_in.txt File could not be opened"<<endl;
    }
    ////////////////***********************************************************************************
    if(variable_out.size() != 0)
    {
    if(variable_out[0] != "0")////number of function
    {
        outkmap<<(variable_next.size()+variable_out.size())<<endl;////number of function
        for(int i = 0 ;i<variable_next.size();i++)////output next 0101
        {
            outkmap<<(variable_present.size()+variable_in.size())<<endl;//number of each variable
            for(int j = 0;j<next_stt.size()/variable_next.size();j++)
            {
                outkmap<<next_stt[j*variable_next.size()+i]<<" ";
            }
            outkmap << endl;
        }
        for(int i = 0 ;i<variable_out.size();i++)////output out 0101
        {
            outkmap<<(variable_present.size()+variable_in.size())<<endl;//number of each variable
            for(int j = 0;j<output.size()/variable_out.size();j++)
            {
                //cout <<"j: "<< j<<"[j*variable_out.size()+i]: "<<j*variable_out.size()+i<<endl;
                outkmap<<output[j*variable_out.size()+i]<<" ";
            }
            outkmap << endl;
        }

    }
    else if(variable_out[0] == "0")//no putput
    {
        outkmap<<(variable_next.size())<<endl;////number of function
        //outkmap<<(variable_present.size()+variable_in.size())<<endl;//number of each variable
        for(int i = 0 ;i<variable_next.size();i++)
        {
            outkmap<<(variable_present.size()+variable_in.size())<<endl;//number of each variable
            for(int j = 0;j<next_stt.size()/variable_next.size();j++)
            {
                outkmap<<next_stt[j*variable_next.size()+i]<<" ";
            }
            outkmap << endl;
        }
    }
    }
    outkmap.close();
    ////////////////////////////////////*************************************************************
    //cout << "The output file successfully exported!"<<endl;
    ////////////////////////////////////////////////////

    ////////////-------------------top--------------------///////////////
    top();
    ////////////////----------------------------
    string temp_bench,temp_text;
    vector<string> bench_1,bench_2,temp_each,temp_each_1,not_gate,and_gate_stt,and_gate_out,and_gate_choose,or_gate_choose;
    ifstream inresult("kmap_out.txt",ios::in);
    int inverter_num=0,and_num=0,or_num=0;
    while(!inresult)
    {
        cerr << "The file is not found."<<endl;
        //cout << "Please enter the name of the input file again: ";
        inresult.open("kmap_out.txt",ios::in);
        if(inresult)
        {
            break;
        }

    }
    //cout << "Loading the file..."<<endl;
    ///////////////////////////////////////////////////input kmap_out//////////////////////////
    //size_t filesize = FileSize(inresult);
    for (int i = 0; i<100;i++)
    {
        //cout <<"i: "<<i<<endl;
        inresult>>temp_bench;
        bench_1.push_back(temp_bench);
        /*if(inresult.eof())
        {
            cout <<"i: "<<i<<endl;
            break;
        }*/
    }
    bench_1.pop_back();
    //cout << "bench \n";
    /*for(int i = 0;i<bench_1.size();i++)
    {
        cout <<"i: "<<i<<" "<<bench_1[i]<<endl;
    }*/
    ////////////////////////////////make num be variable and find number of inverter/////////////
    //cout<<bench_1[0][0]<<endl;

    for(int i = 0;i < bench_1.size();i++)
    {

        if(bench_1[i][0] == '#')
        {
            bench_2.push_back(bench_1[i]);
            and_gate_choose.push_back(bench_1[i]);
            //cout <<"meet #"<<endl;
            //temp_each.push_back(bench_1[i]);
            for(int j = i+1;j < bench_1.size();j++)
            {
                //cout <<"開始給數字"<<endl;
                if(bench_1[j][0] == '#')
                {
                    //cout<<"break!!!!"<<endl;
                    break;
                }
                temp_bench = bench_1[j];
                temp_each.push_back(temp_bench);
                //for(int h = 0;h<)

                //cout <<"temp_each.size(): "<<temp_each.size()<<endl;
                if((j-i)%(variable_in.size()+variable_present.size())==0)
                {
                    //cout<<"屬玩3個拉"<<endl;
                    for(int k = 0 ; k < temp_each.size();k++)
                    {
                        //cout <<"k: "<<k<<"temp_each: "<<temp_each[k]<<endl;
                        //cout <<"variable_size: "<<variable_present.size()<<endl;
                        if(k < variable_present.size())////use present
                        {
                            if(temp_each[k] == "0")
                            {
                                //cout << "p0000000"<<endl;
                                inverter_num++;
                                //cout <<"inver "<<inverter_num<<endl;
                                temp_text = "!";
                                temp_text.append(variable_present[k]);
                                bench_2.push_back(temp_text);
                                temp_each_1.push_back(temp_text);
                            }
                            else if(temp_each[k] == "1")
                            {
                                //cout << "p111111"<<endl;
                                temp_text = variable_present[k];
                                //cout << "variable_present["<<k<<"]: "<< variable_present[k]<<endl;
                                bench_2.push_back(temp_text);
                                temp_each_1.push_back(temp_text);
                            }
                            else if(temp_each[k] == "2")
                            {
                                //cout << "p222222"<<endl;
                                temp_text = "U";
                                bench_2.push_back(temp_text);
                                temp_each_1.push_back(temp_text);
                            }
                        }
                        else//use output
                        {
                            if(temp_each[k] == "0")
                            {
                                //temp_text = "!";
                                //cout << "ooo0000000000"<<endl;
                                inverter_num++;
                                //cout << "inverter: "<<inverter_num<<endl;
                                temp_text = "!";
                                temp_text.append(variable_in[k-variable_present.size()]);
                                bench_2.push_back(temp_text);
                                temp_each_1.push_back(temp_text);
                            }
                            else if(temp_each[k] == "1")
                            {
                                //cout << "ooo11111111"<<endl;
                                //cout <<"sizzzzzzzzzzzzzzzz"<<k-variable_present.size()<<endl;
                                //cout << "variable_out.size() "<<variable_in.size()<<endl;
                                temp_text = variable_in[k-variable_present.size()];
                                bench_2.push_back(temp_text);
                                temp_each_1.push_back(temp_text);
                            }
                            else if(temp_each[k] == "2")
                            {
                                //cout << "ooo2222222"<<endl;
                                temp_text = "U";
                                bench_2.push_back(temp_text);
                                temp_each_1.push_back(temp_text);
                            }
                        }
                    }
                int m = 0,and_num_each=0;//record the number of don't care
                for(int l = 0 ; l <temp_each_1.size();l++)
                {
                    if(temp_each_1[l] == "U")
                    {
                        m++;
                        //cout << "-_________________________m: "<<m<<endl;
                    }
                    if(m<(variable_present.size()+variable_in.size()-1)&&l == temp_each_1.size()-1)
                    {
                        and_num++;//////and gate number
                        and_num_each++;
                    }
                }
                string temp_and;//logic and for each

                for(int l = 0 ; l <temp_each_1.size();l++)//
                {
                    if(temp_each_1[l] == "U")
                    {
                        continue;
                    }
                    if(and_num_each>0)
                    {
                        //if()//
                        //cout <<l<<" find and gate number: "<<and_num_each<<endl;
                        if(temp_and.length()==0)
                        {
                            temp_and = temp_each_1[l];
                        }
                        else
                        {
                            //cout <<"meeeeeeeeeee: "<<l<<endl;
                            temp_and.append(",");
                            temp_and.append(temp_each_1[l]);
                        }
                    }
                }
                //cout << "and_gate_choose.size(): "<<and_gate_choose.size()<<endl;
                if(and_num_each>0)
                {
                    if(and_gate_choose.size() < variable_present.size()+variable_in.size())
                    {
                        and_gate_stt.push_back(temp_and);
                    }
                    else
                    {
                        and_gate_out.push_back(temp_and);
                    }

                }

                temp_each.clear();
                temp_each_1.clear();
                }
                else
                {
                    continue;
                }

            }
            //temp_each.clear();
        }
        else
        {
            continue;
        }

    }
    ////////////////----------------------------
    for(int i = 0 ; i < and_gate_stt.size();i++)
    {
        auto pos = findIndex(and_gate_stt,and_gate_stt[i]);
        //cout << "i: "<<i<<" P: "<<pos<<endl;
        if(pos == -1)
        {
            continue;
        }
        else if(pos<i)
        {
            //and_gate_stt.erase(pos);
            //cout << "iiiiiiiiii: "<<i<<" PPPPPPPPPPPPPPPPP: "<<pos<<endl;
            and_gate_stt.erase(and_gate_stt.begin()+pos);
            and_num--;
            i--;

        }
        //and_gate_stt.remove();
    }
    /*string temp_or;
    int head = 0,tail = 0,bet = 0;
    for(int i = 0 ; i < bench_2.size()-1;i++)
    {
        if(bench_2[i][0] == '#' && (bench_2[i][1]-bench_2[head][1])==1)////meet 2 # to calculate or_num
        {
            tail = i;
            bet = tail - head - 1;
            if((bet/(variable_present.size()+variable_in.size()))>=2)
            {
                for(int j = head;j<i;j++)
                {
                    if(bench_2[j] == "U"||bench_2[j][0] == '#')
                    {
                        continue;
                    }
                    if(temp_or.length()==0)
                    {
                        temp_or = bench_2[i];
                    }
                    else
                    {
                        temp_or.append(",");
                        temp_or.append(bench_2[j]);
                    }
                }
                cout << "temp_or: "<<temp_or<<endl;
                or_gate_choose.push_back(temp_or);
                or_gate_choose.push_back("||");
                head = i;
            }
        }
        else if (i == bench_2.size()-1)//when it's last of this for loop
        {
            //cout <<"hpooooooooooo"<<endl;
            tail = i;
            bet = tail - head;
            if((bet/(variable_present.size()+variable_in.size()))>=2)
            {
                for(int j = head;j<i;j++)
                {
                    if(temp_each_1[j] == "U"||bench_2[j][0] == '#')
                    {
                        continue;
                    }
                    if(temp_or.length()==0)
                    {
                        temp_or = temp_each_1[i];
                    }
                    else
                    {
                        temp_or.append(",");
                        temp_or.append(temp_each_1[j]);
                    }
                }
                cout << "temp_or: "<<temp_or<<endl;
                or_gate_choose.push_back(temp_or);
                or_gate_choose.push_back("||");
                head = i;
            }
            //or_num = or_num + (gap/(variable_present.size()+variable_in.size())) - 1;
        }
        //cout <<"i: "<<i<<" or_num: "<<or_num<<endl;
    }*/
    /*
    for(int i=0;i<or_gate_choose.size();i++)
    {
        cout << "i: "<<i<<" "<<or_gate_choose[i]<<endl;
    }*/
    //cout << "~~~~~~~~~~~~~and gate state~~~~~~~~~"<<endl;
    /*for(int i=0;i<and_gate_stt.size();i++)
    {
        cout << "i: "<<i<<" "<<and_gate_stt[i]<<endl;
    }*/
    /////////////////////////////////////
    //////////////////////////////////find number of or gate
    int start=0,endd=0,gap=0;

    //cout <<bench_2[0][1]<<" "<<bench_2[7][1]<<endl;
    //cout <<"+++++++++++++++"<<(bench_2[7][1]-bench_2[0][1])<<endl;
    for(int i = 0 ; i < bench_2.size()-1;i++)
    {

        /*if(bench_2[i][0] == "#")
        {
            start = i;
        }*/
        //cout <<"i: "<<i<<endl;
        if(bench_2[i][0] == '#' && (bench_2[i][1]-bench_2[start][1])==1)////meet 2 # to calculate or_num
        {
            //cout <<"heeeeeeeeee"<<endl;

            endd = i;
            gap = endd - start - 1;
            or_num = or_num + (gap/(variable_present.size()+variable_in.size())) - 1;
            start = i;

        }
        else if (i == bench_2.size()-1)//when it's last of this for loop
        {
            //cout <<"hpooooooooooo"<<endl;
            endd = i;
            gap = endd - start;
            or_num = or_num + (gap/(variable_present.size()+variable_in.size())) - 1;
        }
        //cout <<"i: "<<i<<" or_num: "<<or_num<<endl;
    }
    //cout <<" or_num: "<<or_num<<endl;
    //////////////////////////////////
    ///////////////////////////////////////////////make variable into gate

    /////////////////////////////////////////////////
    ///////////////////////////////not
    for(int i = 0;i <bench_2.size();i++)
    {
        if(bench_2[i][0] == '!')
        {
            not_gate.push_back(bench_2[i]);
        }
    }
    ////////////////----------------------------
    ofstream outbench(argv[2],ios::out);
    if(!outbench)
    {
        cerr << "kmap.o File could not be opened"<<endl;
    }
    //cout << "Exporting the file..."<<endl;
    /////////////////////////////input number
    if(variable_in.size()>0)
    {
        if(variable_in[0] == "0")
        {
            outbench<<"# 0 "<<"input"<<endl;
        }
        else if(variable_in.size()>1)
        {
            outbench<<"# "<<variable_in.size()<<" "<<"inputs"<<endl;
        }
        else
        {
            outbench<<"# "<<variable_in.size()<<" "<<"input"<<endl;
        }
    }
    else
    {
        outbench<<"# 0 input"<<endl;
    }
    ////////////////////////////////////////////////
    /////////////////////////////////output number
    if(variable_out.size()>0)
    {
        if(variable_out[0] == "0")
        {
            outbench<<"# 0 "<<"output"<<endl;
        }
        else if(variable_out.size()>1)
        {
            outbench<<"# "<<variable_out.size()<<" "<<"outputs"<<endl;
        }
        else
        {
            outbench<<"# "<<variable_out.size()<<" "<<"output"<<endl;
        }
    }
    else
    {
        outbench<<"# 0 output"<<endl;
    }
    /////////////////////////////////////////////////////
    //////////////////inverter number
    if(inverter_num>1)
    {
        outbench<<"# "<<inverter_num<<" "<<"inverters"<<endl;
    }
    else
    {
        outbench<<"# "<<inverter_num<<" "<<"inverter"<<endl;
    }
    /////////////////////////////////////////////////////
    ///////////////////////fli-flop number////////////////
    if(variable_next.size()>1)
    {
        outbench<<"# "<<variable_next.size()<<" "<<"flip-flops"<<endl;
    }
    else
    {
        outbench<<"# "<<variable_next.size()<<" "<<"flip-flop"<<endl;
    }
    ////////////////////////////////////////////////////
    ////////////////////gate number/////////////////////
    if(and_num+or_num>1)
    {
        if(and_num > 1 && or_num > 1)
        {
            outbench<<"# "<<(and_num+or_num)<<" gates ("<<and_num<<" "<<"ANDs + "<<or_num<<" ORs)"<<endl;
        }
        else if(and_num <= 1 && or_num > 1)
        {
            outbench<<"# "<<(and_num+or_num)<<" gates ("<<and_num<<" "<<"AND + "<<or_num<<" ORs)"<<endl;
        }
        else if(and_num <= 1 && or_num <= 1)
        {
                outbench<<"# "<<(and_num+or_num)<<" gates ("<<and_num<<" "<<"AND + "<<or_num<<" OR)"<<endl;
        }
        else if(and_num > 1 && or_num <= 1)
        {
            outbench<<"# "<<(and_num+or_num)<<" gates ("<<and_num<<" "<<"ANDs + "<<or_num<<" OR)"<<endl;
        }
    }
    else
    {
        if(variable_present.size() == 1&&variable_in.size()==2)
        {
            outbench<<"# "<<(and_num+or_num+1)<<" gates ("<<and_num<<" "<<"AND + "<<or_num+1<<" OR)"<<endl;
        }
        else
        {
            outbench<<"# "<<(and_num+or_num)<<" gate ("<<and_num<<" "<<"AND + "<<or_num<<" OR)"<<endl;
        }
    }
    ////////////////----------------------------

    outbench<<endl;
    if(variable_in.size()>0)
    {
        if(variable_in[0] != "0")
        {
            for(int i = 0 ;i<variable_in.size();i++)
            {
                outbench<<"INPUT("<<variable_in[i]<<")"<<endl;
            }
            outbench<<endl;
        }

        if(variable_out[0] != "0")
        {
            for(int i = 0 ;i<variable_out.size();i++)
            {
                outbench<<"OUTPUT("<<variable_out[i]<<")"<<endl;
            }
        //outbench<<"OUTPUT("<<variable_out[i]<<")"<<endl;
        outbench<<endl;
        }
    }
    ///////////////////////////////not gate
    for(int i = 0 ; i < not_gate.size();i++)
    {
        outbench<<not_gate[i]<<" = NOT("<<not_gate[i][1]<<")"<<endl;
    }
    ////////////////////////////////////////and gate  state

    for(int i = 0;i<and_gate_stt.size();i++)
    {
        outbench<<"N"<<(i+1)<<" = AND("<<and_gate_stt[i]<<")"<<endl;
    }
    ///////////////////////////////////////////or gate
    if(or_num == 0&&variable_present.size()==1)
    {
        outbench << "DA = OR("<<variable_present[0]<<",N"<<or_num+1<<")"<<endl;
    }
    else if(or_num == 2)
    {
        outbench << "DA = OR("<<"N1,"<<"N"<<or_num<<")"<<endl;
        outbench << "DB = OR("<<"N1,"<<"N"<<or_num+1<<")"<<endl;
    }

    ///////////////////////////////////////////
        //////////////////////////////////////////D flip-flop
    for(int i = 0;i<variable_next.size();i++)
    {
        outbench << variable_next[i]<<" = D(D"<<variable_next[i]<<",CLK)"<<endl;
    }
    //////////////////////////////////////////
    ///////////////////////////////////////and gate output
    for(int i = 0;i<and_gate_out.size();i++)
    {
        outbench<<variable_out[i]<<" = AND("<<and_gate_out[i]<<")"<<endl;
    }
    /////////////////////////////////////////

    outbench<<"#END";
    return 0;
}
