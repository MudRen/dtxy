#include <ansi.h>
#include <room.h>
inherit ROOM;
int do_lingwu();
int finish(object who);
int finish2(object who);
void create()
{
set("short", "混沌");
set("long", @LONG
    
这个空间是盘古使用自己的神力制造出来的。
和当初盘古出生、破开的混沌非常相似。
看来你可以在这里领悟（lingwu）到一些东西。
 
LONG );
setup();
}
void init() 
{
    add_action ("do_lingwu","lingwu");
}

int do_lingwu()
{
  	object who = this_player();
  	if( who->query("kai_cant") )
  	{
  		message_vision(HIY"你对开天辟地的认识，已经到了你的极限。\n"NOR,who);
  		return 1;
  	}
  	if( !who->query_temp("kai_learn") )
  	{
  		message_vision(HIY"你是怎么进来的？！\n"NOR,who);
  		return 1;
  	}
  	if( who->query_temp("kai_learning") )
  	{
  		message_vision(HIY"你正在领悟。\n"NOR,who);
  		return 1;
  	}
  	message_vision(HIY"$N仔细体会着世界初始的状态，慢慢物我两忘。\n"NOR,who);
	who->set_temp("kai_learning",1);
	who->start_busy(20);
	if( !who->query("kai_known") && random(who->query("int")) > 20 - random( who->query("lunhui_zhuanshi") ) )
		call_out("finish",10,who);
	else if( who->query("kai_known") == 1 && random(who->query("int")) > 25 - random( who->query("lunhui_zhuanshi") ) )
		call_out("finish",10,who);
	else if( who->query("kai_known") == 2 && random(who->query("int")) > 30 - random( who->query("lunhui_zhuanshi") ) )
		call_out("finish",10,who);
	else
		call_out("finish2",10,who);
	return 1;
}

int finish(object who)
{
	object downroom = load_object(__DIR__"sleep");
	if(base_name(environment(who)) != "/d/jjf/hundun")
	{
		message_vision(HIY"$N离开了混沌，领悟被中断。\n"NOR,who);
		who->delete_temp("kai_learning");
		who->delete_temp("kai_learn");
		return 1;
	}
	message_vision(HIY"$N记起盘古斧头劈出的方式，心中若有所悟！\n"NOR,who);
	message_vision(HIY"盘古的动作不停的在$N脑海中重放！\n"NOR,who);
	message_vision(HIY"$N豁然顿悟：盘古所传开天辟地实是要还原于混沌的功法！\n"NOR,who);
	if( !who->query("kai_known") )
	{
		message_vision(HIY"$N一声长啸，劈出两斧，却发现以自己的功力竟然无法后继！\n"NOR,who);
		message_vision(HIY"突然$N又感受到了周围的世界！\n"NOR,who);
		who->set("kai_known",1);
		who->delete_temp("kai_learn");
     		who->delete_temp("kai_learning");
		who->move("/d/jjf/sleep");
		message_vision(HIY"一个身影，突然出现在你眼前！\n"NOR,downroom);
		message("chat",HIC+"\n\n〖"+HIW+"惊天谣传"+HIC+"〗盘古(pan gu)：" + who->name() + "经过不断努力，终于领悟了"+HIM"[开天辟地]"+HIC"！\n\n\n"NOR,users());
		return 1;
	}
	if( who->query("kai_known") == 1 )
	{
		message_vision(HIY"$N一声长啸，劈出三斧，却发现以自己的功力竟然无法后继！\n"NOR,who);
		message_vision(HIY"突然$N又感受到了周围的世界！\n"NOR,who);
		who->set("kai_known",2);
		who->delete_temp("kai_learn");
     		who->delete_temp("kai_learning");
		who->move("/d/jjf/sleep");
		message_vision(HIY"一个身影，突然出现在你眼前！\n"NOR,downroom);
		message("chat",HIC+"\n\n〖"+HIW+"惊天谣传"+HIC+"〗盘古(pan gu)：" + who->name() + "经过不断努力，将"+HIM"[开天辟地]"+HIC"的威力提高了一个档次！\n\n\n"NOR,users());
		return 1;
	}
	if( who->query("kai_known") == 2 )
	{
		message_vision(HIY"$N一声长啸，劈出四斧，却发现以自己的功力竟然无法后继！\n"NOR,who);
		message_vision(HIY"突然$N又感受到了周围的世界！\n"NOR,who);
		who->set("kai_known",3);
		who->delete_temp("kai_learn");
     		who->delete_temp("kai_learning");
		who->move("/d/jjf/sleep");
		message_vision(HIY"一个身影，突然出现在你眼前！\n"NOR,downroom);
		message("chat",HIC+"\n\n〖"+HIW+"惊天谣传"+HIC+"〗盘古(pan gu)：" + who->name() + "经过不断努力，终于掌握了"+HIM"[开天辟地]"+HIC"全部威力！\n\n\n"NOR,users());
		return 1;
	}
	return 1;	
}

int finish2(object who)
{
	object downroom = load_object(__DIR__"sleep");
	if(base_name(environment(who)) != "/d/jjf/hundun")
	{
		message_vision(HIY"$N离开了混沌，领悟被中断。\n"NOR,who);
		who->delete_temp("kai_learning");
		who->delete_temp("kai_learn");
		return 1;
	}
	message_vision(HIY"$N自己端详这个空间，琢磨着劈开它的办法！\n"NOR,who);
	message_vision(HIY"$N不断的想象盘古出手的方式，不断的劈砍着空间的外壳！\n"NOR,who);
	message_vision(HIY"可惜$N努力了许久，这个空间也没有松动的现象，$N已经精疲力尽了！\n"NOR,who);
	message_vision(HIY"突然$N又感受到了周围的世界！\n"NOR,who);
	who->set("kai_cant",1);
	who->delete_temp("kai_learn");
     	who->delete_temp("kai_learning");
     	if( !who->query("kai_known") )
		message("chat",HIC+"\n\n〖"+HIW+"惊天谣传"+HIC+"〗盘古(pan gu)：" + who->name() + "脑筋太死、悟性不足，无法领悟"+HIM"[开天辟地]"+HIC"，真是可惜啊！\n\n\n"NOR,users());
	else
		message("chat",HIC+"\n\n〖"+HIW+"惊天谣传"+HIC+"〗盘古(pan gu)：" + who->name() + "脑筋太死、悟性不足，无法领悟更高的"+HIM"[开天辟地]"+HIC"，真是可惜啊！\n\n\n"NOR,users());
	message_vision(HIY"一个身影，突然出现在你眼前！\n"NOR,downroom);
	who->move("/d/jjf/sleep");
	who->unconcious();
	return 1;	
}