#include <ansi.h>
inherit ROOM;
int do_lingwu();
int check(object who);
void create ()
{
  set ("short", "广场");
  set ("long", @LONG

这里就是蜀山历代经营的圣地广场，广场四周有七个高大的门楼，上面写一丈大的“剑”字。

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
        		return notify_fail("以你的境界，进入会有危险！\n");
        	else 
              		return ::valid_leave(who, dir);
        }
        else if( dir == "3" )
        {
        	if( who->query("sword_known") < 2 )
        		return notify_fail("以你的境界，进入会有危险！\n");
        	else 
              		return ::valid_leave(who, dir);
        }
        else if( dir == "4" )
        {
        	if( who->query("sword_known") < 3 )
        		return notify_fail("以你的境界，进入会有危险！\n");
        	else 
              		return ::valid_leave(who, dir);
        }
        else if( dir == "5" )
        {
        	if( who->query("sword_known") < 4 )
        		return notify_fail("以你的境界，进入会有危险！\n");
        	else 
              		return ::valid_leave(who, dir);
        }
        else if( dir == "6" )
        {
        	if( who->query("sword_known") < 5 )
        		return notify_fail("以你的境界，进入会有危险！\n");
        	else 
              		return ::valid_leave(who, dir);
        }
        else if( dir == "7" )
        {
        	if( who->query("sword_known") < 6 )
        		return notify_fail("以你的境界，进入会有危险！\n");
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
		message_vision("你没有带剑，怎么领悟剑心？ :)\n",who);
		return 0;
	}
	if( who->query("sword_cant") )
		return 0;
  	if( who->query("sword_known") != 7 )
  	{
  		return 0;
  	}
  	message_vision(HIC"$N捧剑静坐，尝试与剑灵沟通。\n"NOR,who);
  	who->start_busy(6);
	call_out("check",5,who);
	return 1;  
}

int check(object who)
{
	object jian;
	message_vision(HIY"$N冥冥中，似有所悟。\n"NOR,who);
	message_vision(HIY"$N将意念化作细丝，慢慢融入剑中。\n"NOR,who);
	message_vision(HIY"$N彷佛听到一声轰鸣，意念已经完全进入了一个空旷的天地。\n"NOR,who);
	jian = new("/d/shushan/npc/jianling");
	jian->copy_status(jian,who,11);
	jian->move("/d/shushan/shengdi/sword_room");
	who->move("/d/shushan/shengdi/sword_room");
	return 1;
}