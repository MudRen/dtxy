// Room: /d/death/walk.c
#include <ansi.h>

inherit ROOM;

void create ()
{
  set ("short", HIR"鬼门关"NOR);
  set ("long", @LONG

隐约北方现出一座黑色城楼，城楼上有一幅金匾，上面刻着“幽冥
界”三个大字。城楼下城门紧闭，黑漆漆地什么也看不清楚。路边
一个破木牌直直地指向北方，周围只有少许暗红色的火光若隐若现
地闪烁着。
LONG);

  set("exits", ([ /* sizeof() == 3 */
  "east" : __DIR__"new-out5",
  "west" : __DIR__"new-out7",
  "south": __DIR__"gate",
]));
  set("hell", 1);

  setup();
}

void init()
{
        //object me=this_player();
	//	remove_call_out("greeting");
        //        call_out("greeting", 60, me);
	add_action("do_pass", "north");
	add_action("do_break", "break");
}
void greeting(object ob)
{
        if( !ob || environment(ob) != this_object() ) return;
	ob->set_temp("time_enough", 1);
	return;
}
int do_pass()
{
	object me=this_player();
	
	//if( me->is_ghost() && !me->query_temp("time_enough") )
	//	return notify_fail("城楼上隐约传来喊声：阳气太盛，不得入城！\n");

	//if( me->is_ghost() ) {
	//	me->reincarnate();
	//	me->set("gin", (int)me->query("max_gin"));
	//	me->delete_temp("time_enough");
	//}

	tell_object(me, "你直直地向北对着城门走去，居然发现黑色的城门只是道气帘。。。\n");
	tell_room(environment(me), me->name()+"直直地向北对着城门走去，居然从紧闭的门中穿了过去！\n",
({me, me}));
	me->move("/d/death/new-zhaopo");
	tell_room(environment(me), me->name()+"走了过来。\n", ({me, me}));
	return 1;
}

int do_break()
{
	object me=this_player();
	if( !me->query_temp("jingtian/jiejie") )
		return 0;
	if( me->is_busy() )
	{
		tell_object(me, "你正忙着呢。。。\n");
		return 1;
	}
	if( me->query("force") < 1000 )
	{
		tell_object(me, "你内力太低了。。。\n");
		return 1;
	}
	me->start_busy(2);
	me->add("force",-100);
	message_vision("$N奋力向城门击下！\n",me);
	if( random(me->query("kar")) > 25 )
	{
		message_vision("城门发出一声脆响，碎成了粉末，接着又被阴风吹散了！\n",me);
		me->delete_temp("jingtian");
		if( random(me->query("int")) > 17 )
		{
			me->add("jingtian_known",1);
			message("chat",HIC+"\n\n〖"+HIW+"惊天谣传"+HIC+"〗 玉皇大帝(yuhuang dadi)：大事不好，" + me->name() + "把鬼门关的结界打碎了，赶紧去西天请如来佛祖一起商量对策！\n\n"NOR,users());
   			message("chat",HIC+"\n\n〖"+HIW+"惊天谣传"+HIC+"〗冥王(ming wang)：" + me->name() + "打碎鬼门关结界，助我重新入主地府，终于学会了"+HIB"[惊天三式－－"HIB"离别"HIR"亢怒"HIC"式"HIB"]"+HIC"！\n\n"NOR,users());
   			message("chat",HIC+"\n\n〖"+HIW+"惊天谣传"+HIC+"〗冥王(ming wang)：冥界皆尊我为主，我冥界从此后与天庭、佛界鼎足三分！\n\n\n"NOR,users());
		}
		else
		{
			me->set("jingtian_cant",1);
			message("chat",HIC+"\n\n〖"+HIW+"惊天谣传"+HIC+"〗 玉皇大帝(yuhuang dadi)：大事不好，" + me->name() + "把鬼门关的结界打碎了，赶紧去西天请如来佛祖一起商量对策！\n\n"NOR,users());
   			message("chat",HIC+"\n\n〖"+HIW+"惊天谣传"+HIC+"〗冥王(ming wang)：" + me->name() + "打碎鬼门关结界，助我重新入主地府，可惜不能炼化地府怨气，无法练成"+HIB"[惊天三式－－"HIB"离别"HIR"亢怒"HIC"式"HIB"]"+HIC"！\n\n"NOR,users());
   			message("chat",HIC+"\n\n〖"+HIW+"惊天谣传"+HIC+"〗冥王(ming wang)：冥界皆尊我为主，我冥界从此后与天庭、佛界鼎足三分！\n\n\n"NOR,users());
		}
	}
	else
		message_vision("城门上泛起阵阵涟漪，不一会又归于平静！\n",me);
	return 1;
}