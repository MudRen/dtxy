#include <ansi.h>
inherit ROOM;
int do_lingwu();
int check(object who);
void create ()
{
  set ("short", "�㳡");
  set ("long", @LONG

���������ɽ������Ӫ��ʥ�ع㳡���㳡�������߸��ߴ����¥������дһ�ɴ�ġ������֡�

LONG);

  set("exits", ([
  	"1"   : __DIR__"room1",
 	"2"   : __DIR__"room2",
 	"3"   : __DIR__"room3",
	"4"   : __DIR__"room4",
 	"5"   : __DIR__"room5",
 	"6"   : __DIR__"room6",
 	"7"   : __DIR__"room7",
              ]));
	set("outdoors", 1);
  setup();
}
void init() 
{
    add_action ("do_lingwu","lingwu");
}
int valid_leave(object who, string dir)
{
        if( dir == "2" )
        {
        	if( who->query("sword_known") < 1 )
        		return notify_fail("����ľ��磬�������Σ�գ�\n");
        	else 
              		return ::valid_leave(who, dir);
        }
        else if( dir == "3" )
        {
        	if( who->query("sword_known") < 2 )
        		return notify_fail("����ľ��磬�������Σ�գ�\n");
        	else 
              		return ::valid_leave(who, dir);
        }
        else if( dir == "4" )
        {
        	if( who->query("sword_known") < 3 )
        		return notify_fail("����ľ��磬�������Σ�գ�\n");
        	else 
              		return ::valid_leave(who, dir);
        }
        else if( dir == "5" )
        {
        	if( who->query("sword_known") < 4 )
        		return notify_fail("����ľ��磬�������Σ�գ�\n");
        	else 
              		return ::valid_leave(who, dir);
        }
        else if( dir == "6" )
        {
        	if( who->query("sword_known") < 5 )
        		return notify_fail("����ľ��磬�������Σ�գ�\n");
        	else 
              		return ::valid_leave(who, dir);
        }
        else if( dir == "7" )
        {
        	if( who->query("sword_known") < 6 )
        		return notify_fail("����ľ��磬�������Σ�գ�\n");
        	else 
              		return ::valid_leave(who, dir);
        }
        else
        {
            	return ::valid_leave(who, dir);
        }
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
  	if( who->query("sword_known") != 7 )
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
	jian->copy_status(jian,who,11);
	jian->move("/d/shushan/shengdi/sword_room");
	who->move("/d/shushan/shengdi/sword_room");
	return 1;
}