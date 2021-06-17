#include <ansi.h>
inherit ROOM;
int do_lingwu();
int check(object who);
void create ()
{
  set ("short", "����");
  set ("long", @LONG

��������ɽʥ�ص�һ�����ң����������������(lingwu)һ�£������Լ��Ļ�Ե��

LONG);

  setup();
}
void init() 
{
    add_action ("do_lingwu","lingwu");
}

int do_lingwu()
{
  	object who = this_player();
  	object weapon;
    	if (!objectp(weapon = who->query_temp("weapon")) ||
		(string)(weapon->query("skill_type")) != "sword")
	{
		message_vision("��û�д�������ô�����ģ� :)\n",who);
		return 0;
	}
	if( who->query("sword_cant") )
		return 0;
  	if( who->query("sword_known") )
  	{
  		return 0;
  	}
  	message_vision(HIC"$N���������������뽣�鹵ͨ��\n"NOR,who);
  	who->start_busy(6);
	call_out("check",5,who);
	return 1;  
}

int check(object who)
{
	object jian;
	message_vision(HIY"$Nڤڤ�У���������\n"NOR,who);
	message_vision(HIY"$N�������ϸ˿���������뽣�С�\n"NOR,who);
	message_vision(HIY"$N�ݷ�����һ�������������Ѿ���ȫ������һ���տ�����ء�\n"NOR,who);
	jian = new("/d/shushan/npc/jianling");
	jian->copy_status(jian,who,5);
	jian->move("/d/shushan/shengdi/sword_room");
	who->move("/d/shushan/shengdi/sword_room");
	return 1;
}