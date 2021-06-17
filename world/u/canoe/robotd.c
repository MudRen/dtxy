/*robotd.c 2000-8-17 03:37����*/

#include <ansi.h>
#define TIME 60

string *graph_nums=({
"������   ��   ������ ������ ��  �� ������ ������ ������ ������ ������ ",
"��  ��   ��       ��     �� ��  �� ��     ��         �� ��  �� ��  �� ",
"��  ��   ��       ��     �� ��  �� ��     ��         �� ��  �� ��  �� ",
"��  ��   ��   ������ ������ ������ ������ ������     �� ������ ������ ",
"��  ��   ��   ��         ��     ��     �� ��  ��     �� ��  ��     �� ",
"��  ��   ��   ��         ��     ��     �� ��  ��     �� ��  ��     �� ",
"������   ��   ������ ������     �� ������ ������     �� ������ ������ ",
});

string *colours=({
	HIR, HIY, HIW, HIM, YEL, HIB, MAG, RED, 
	});

mapping types=([
	"����"	:	({
"��","��","¿","ţ","��","��","����","����","¹","ѱ¹",
"����¹","����","������","������","����","������","Ϭţ",
"����","è","ʨ��","���","���ޱ�","�ϻ�","���ϻ�","������",
"��ţ","��","�","������","ˮ̡","��","�๷","��","����","����",
"������","ѩ��","��","����","Ұ��","��","����","����","����",
"������","������","����","����Գ","̡��","ʳ����","Ѽ����","����",
"������","���","����","����","��","����","����","����","��˿��",
"����è","С��è"}),
	"�߲�"	:	({
"����","������","«��","�ƹ�","����","�˶�","���","����",
"��","������","���ܲ�","�˻�","��Ҭ��","�϶�","���Ĳ�",
"����","��","��","ݫ��","�۲�","�²�","�ܲ�","Ģ��","ѩά��",
"ϸҶ��","ӥ�춹","��ݤ��","ˮ���","�����˶�","��","����",
"���ȶ�","�㶹","�����","�ඹ","��ѿ","���","����","���",
"�Ϲ�","����","ź","���빽","ƽ��","�㹽","���Ĳ�","ë��",
"����"}),
	"ˮ��"	:	({
"ƻ��","��","��","��","ˮ����","���","����","�㽶","����",
"����","����","���","��","����","â��","��ݮ","����","ɣ�",
"����","ӣ��","ʯ��","�޻���","����","����","����","���",
"����","��","��","�ɿ�","Խ��","��ݮ","����","���","��ľ��",
"ʯ��","��֦","����","⨺���","���ܹ�"}),
	"����"	:	({
"�ž黨","�ﺣ��","������","ɽ��","����ܰ","������","����","�ջ�",
"������","����","������","꼻�","������","����","����","����",
"�ٺ�","ľ����","������","���Ȼ�","ˮ�ɻ�","������","����","ĵ��",
"��ҩ","����","õ��","�¼�","����","���ɻ�","������","������",
"������"}),
]);


mapping query_know_question()
{
	string *lists;
	string quest_list, random_list, tmp_list;
	string *answers;
	int i, true_num;
	mapping answer;

	answer=([
		"quest" : "",
		"answer": 0,
	]);
	lists=keys(types);
	answers=allocate(4);
	switch(random(3))
	{
		case 0:
			quest_list=lists[random(sizeof(lists))];
			true_num=random(4);
			answers[true_num]=types[quest_list][random(sizeof(types[quest_list]))];
			for(i=0;i<4;i++)
			{
				random_list=lists[random(sizeof(lists))];
				if(i==true_num)
					continue;
				tmp_list=types[random_list][random(sizeof(types[random_list]))];
				if(random_list==quest_list ||
				member_array(tmp_list, answers)!=-1)
					i--;
				else answers[i]=tmp_list;
			}
			answer["quest"]=sprintf("����������Ʒ��ѡ������%s�ģ�\n", quest_list);
			break;
		case 1:
			quest_list=lists[random(sizeof(lists))];
			true_num=random(4);
			answers[true_num]=types[quest_list][random(sizeof(types[quest_list]))];
			do{
				random_list=lists[random(sizeof(lists))];
			}while(quest_list==random_list);

			for(i=0;i<4;i++)
			{
				if(i==true_num)
					continue;
				tmp_list=types[random_list][random(sizeof(types[random_list]))];
				if(member_array(tmp_list, answers)!=-1)
					i--;
				else answers[i]=tmp_list;
			}
			answer["quest"]=sprintf("����������Ʒ��ѡ��������������ͬ�ģ�\n");
			break;							
		case 2:
			for(i=0;i<4;i++)
			{
				random_list=lists[random(sizeof(lists))];
				if(member_array(random_list, answers)!=-1)
					i--;
				else answers[i]=random_list;
			}
			if(!random(5))
				answers[3]="���϶�����";

			true_num=random(4);
			if(true_num==3 && answers[3]=="���϶�����")
				do{
					quest_list=lists[random(sizeof(lists))];
				}while(member_array(quest_list, answers)!=-1);
			else quest_list=answers[true_num];			
			answer["quest"]=sprintf("%s������������ࣺ\n", types[quest_list][random(sizeof(types[quest_list]))]);
			break;
	}
	for(i=0;i<4;i++)
		answer["quest"]+=sprintf("%d. %s\n", i, answers[i]);
	answer["answer"]=true_num;
	return answer;
}


mapping query_num_question()
{
        int temp, length, *digit, j, k, rand, flag, i;
        mapping answer;

	i=random(9000)+1000;
	answer=([
		"quest"	: "",
		"answer": 0,
	]);
        temp=i;
        for(length=1;;length++)
        {
                temp/=10;
                if(temp<1)
                        break;
        }
        temp=i;
        digit=allocate(length);
        flag=random(3);
        if(flag)
        	rand=random(length);
        else rand=i;
        do{
                digit[length-1]=temp%10;
                temp=temp/10;
                length--;
        }while(length>0);
        temp=random(sizeof(colours));
       	switch(flag)
       	{
       		case 0:
       		answer["quest"]="����ͼ������ɵ������ǣ�\n";
       		break;
       		case 1:
       		answer["quest"]="����ͼ������ɵ������У��������Ĳ�ͬ�ǵڼ������֣�\n";
       		break;
       		case 2:
       		answer["quest"]="����ͼ������ɵ������У���ɫ�������Ĳ�ͬ�ǵڼ������֣�\n";
       		break;
       	}
        for(k=0;k<sizeof(graph_nums);k++)
        {
        	for(j=0;j<sizeof(digit);j++)
        	switch(flag)
        	{
        		case 0:
        		answer["quest"]+=CYN+graph_nums[k][digit[j]*7..digit[j]*7+6]+NOR;
        		break;
        		case 1:
        		if(rand==j)
        			answer["quest"]+=CYN+replace_string(graph_nums[k][digit[j]*7..digit[j]*7+6],
        				"��", "��")+NOR;
        		else answer["quest"]+=CYN+graph_nums[k][digit[j]*7..digit[j]*7+6]+NOR;
        		break;
        		case 2:
        		if(rand==j)
        			answer["quest"]+=colours[temp]
        				+graph_nums[k][digit[j]*7..digit[j]*7+6]+NOR;
        		else answer["quest"]+=CYN+graph_nums[k][digit[j]*7..digit[j]*7+6]+NOR;
        		break;
        	}
                answer["quest"]+="\n";
        }
        answer["answer"]=flag?rand+1:rand;
        return answer;
}

mapping give_question()
{
	mapping question;
	
	if(random(2))
		question=query_num_question();
	else question=query_know_question();
	
	return question;
}