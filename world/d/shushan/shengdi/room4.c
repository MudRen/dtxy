#include <ansi.h>
inherit ROOM;
int do_lingwu();
int check(object who);
void create ()
{
  set ("short", "剑室");
  set ("long", @LONG

这里是蜀山圣地的一个剑室，你可以在这里领悟(lingwu)一下，看看自己的机缘。

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
		message_vision("你没有带剑，怎么领悟剑心？ :)\n",who);
		return 0;
	}
	if( who->query("sword_cant") )
		return 0;
  	if( who->query("sword_known") != 3 )
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
	jian->copy_status(jian,who,8);
	jian->move("/d/shushan/shengdi/sword_room");
	who->move("/d/shushan/shengdi/sword_room");
	return 1;
}