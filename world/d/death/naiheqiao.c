inherit ROOM;
#include <ansi.h>
void create ()
{
  set ("short", "奈何桥");
  set ("long", @LONG

这是一座仅数寸之宽，数长之长的石桥。上有寒风滚滚，下是
血浪滔滔。桥上左右无扶手，险峻之路如同匹练搭长江，桥下
之水阴气逼人，腥风扑鼻。
LONG);

  set("exits", ([ /* sizeof() == 2 */
  "south" : __DIR__"bidouya",
  "north" : __DIR__"huangwai",
]));
  set("hell", 1);
  set("objects", ([ /* sizeof() == 1 */
  __DIR__"npc/shizhe" : 2,
]));

  setup();
}

void init()
{
        add_action("do_xiulian", "xiulian");
}
int do_xiulian()
{       
        object me=this_player();
	if( !me->query_temp("jingtian/lingwu") )
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
	me->start_busy(5);
	me->add("force",-100);
	message_vision("$N盘膝坐下，准备炼化奈何桥上的愁怨仇恨之气！\n",me);
	if( random(me->query("kar")) > 25 )
	{
		message_vision(HIR"桥下的血河突然沸腾起来，血浪滔天，中间还夹着森森白骨！\n"NOR,me);
		message_vision(HIR"两个桥梁使者慌了神：当年，当年冥王大人在这里悟出了惊天绝学就是如此情境，难道。。。\n"NOR,me);
		me->delete_temp("jingtian");
		if( random(me->query("int")) > 25 )
		{
			me->add("jingtian_known",1);
			message_vision(HIR"$N将血浪中的气息吸纳入体，觉得异常的舒服！\n"NOR,me);
   			message("chat",HIC+"\n\n〖"+HIW+"惊天谣传"+HIC+"〗冥王(ming wang)：" + me->name() + "悟性过人，终于掌握了炼化地府阴气的方法，学会了"+HIB"[惊天三式－－"HIB"断肠"HIR"绝灭"HIC"式"HIB"]"+HIC"，前途不可限量！\n\n"NOR,users());
   			message("chat",HIC+"\n\n〖"+HIW+"惊天谣传"+HIC+"〗冥王(ming wang)：哈哈，我冥界又多一超级高手，统一三界的时机到了！\n\n\n"NOR,users());
		}
		else
		{
			me->set("jingtian_cant",1);
			message_vision(HIR"$N将血浪中的气息吸纳入体，只觉得阵阵反胃，哇的吐出一口鲜血！\n"NOR,me);
   			message("chat",HIC+"\n\n〖"+HIW+"惊天谣传"+HIC+"〗冥王(ming wang)：" + me->name() + "悟性不足，无法完全掌握了炼化地府阴气的方法，未能学会"+HIB"[惊天三式－－"HIB"断肠"HIR"绝灭"HIC"式"HIB"]"+HIC"，真是可惜！\n\n"NOR,users());
   			message("chat",HIC+"\n\n〖"+HIW+"惊天谣传"+HIC+"〗冥王(ming wang)：唉，看来统一三界的时机未到，我冥界弟子须加紧练功！\n\n\n"NOR,users());
		}
	}
	return 1;
}

