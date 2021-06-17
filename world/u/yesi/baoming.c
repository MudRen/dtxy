//write by yesi for dtxy
//yeahsi@21cn.com

#include <ansi.h>
inherit ITEM;
inherit F_SAVE;

int top_list1(mapping first, mapping second);
int top_list2(mapping first, mapping second);
mapping *all_biao;

void create()
{
	set_name("ˮ½��ᱨ����", ({ "biao"}) );
	set("long",
		"�����Ҫ�����μ�ˮ½�������(baoming),�鿴��˭����������(chakan)��\n");
	set("unit", "��");
	set("no_put", 1);
	set("no_get", 1);
	set_weight(900000000);
	seteuid(getuid());
	restore();
	
}

void init()
{
	add_action("do_baoming", "baoming");
	add_action("do_chakan", "chakan");
}

string query_save_file()
{
	return DATA_DIR + "baoming";
}


int do_baoming()
{
	object me;
	int pingjia,age;
	mapping biao;
	me = this_player();
	age = me->query("age");
		
	if (me->query("sldh1"))
	   return notify_fail("���Ѿ������ˡ�\n");
	if (age < 16)
	   return notify_fail("16�����ϲ��ܱ�����\n");
	
	biao = ([]);	
	pingjia = "/cmds/usr/top.c"->get_score(me);
	
	 biao = ([
    	"id":me->query("id"),
    	"name":me->query("name"),
    	"age": age,
    	"pingjia":pingjia,
    	         ]);
    	
    	me->set("sldh1",1);
    	
    	 if( !pointerp(all_biao) ) all_biao = ({ biao });
	else all_biao += ({ biao });
	save();
	
	save();
	
	tell_object(me,"�����ɹ���ף���ø������Σ��뿴���µĹ���help sldh_rules����\n");
	return 1;
}

int do_chakan()
{
	mapping* list;
	int number,i;
	number = sizeof(all_biao);
	
	if( !pointerp(all_biao) || !number ) 
		{
			write("\n��û���˱�����\n");
			return 1;
		}
		
	list = sort_array(all_biao, (: top_list1 :));
	list = sort_array(list, (: top_list2 :));
	
	write("���� "+number+" ����ұ�����
ID           ����         �ۺ�����       ����
-----------------------------------------------\n");
	for (i=0;i<number;i++)
	printf("%-10s   %-10s    %-4d           %d \n",
	        list[i]["id"],list[i]["name"],
	        list[i]["pingjia"],list[i]["age"]);
        
        return 1;
}


int top_list1(mapping first, mapping second)
{
    int score1,score2;

    score1 = first["pingjia"];
    score2 = second["pingjia"];

    return score1 - score2;
}	         
	
int top_list2(mapping first, mapping second)
{
    int score1,score2;

    score1 = first["age"];
    score2 = second["age"];

    return score2 - score1;
}	         	
		
	