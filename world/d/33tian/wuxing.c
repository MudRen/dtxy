#include <ansi.h>
#include <room.h>
inherit ROOM;
int do_lingwu();
int check(object who,int k);
int finish(object who);
int finish2(object who);
void create()
{
set("short", "五行空间");
set("long", @LONG
    
这空间内到处都是五行元素，中间有一座大山，甚是雄伟。
 
LONG );
     set("exits/out", __DIR__"dadian");
     set("objects", ([ /* sizeof() == 4 */
       __DIR__"obj/wuxingshan" : 1,
]));
setup();
}
void init() 
{
    call_out ("check_hp", 6+random(5),this_player());
    add_action ("do_lingwu","lingwu");
}
int check_hp(object who)
  {
  object where = this_object();
  if ( (! who)  ||    (! present(who, where)) )  return 1;
  if( who->query("kee") > 100 && who->query("sen") > 100 )
    {
    	switch (random(6))
        {
        	case 0:
                { 
                       	message_vision(HIB"\n四周五行元素一阵混乱，刮起一阵元素风暴，$N被吹的东倒西歪！\n"NOR,who);
                       	who->receive_damage("kee",50);
                      	who->receive_damage("sen",50);
                      	COMBAT_D->report_status(who);
                      	COMBAT_D->report_sen_status(who);
                        break;
               	}
               	case 1:
                { 
                       	message_vision(HIB"\n四周金元素凝成一把利剑，$N被刺的遍体鳞伤！\n"NOR,who);
                       	who->receive_damage("kee",50);
                      	COMBAT_D->report_status(who);
                        break;
               	}
               	case 2:
                { 
                       	message_vision(HIB"\n四周水元素汇聚成一道洪流，$N被冲的东倒西歪！\n"NOR,who);
                       	who->receive_damage("kee",50);
                      	COMBAT_D->report_status(who);
                        break;
               	}
               	case 3:
                { 
                       	message_vision(HIB"\n四周木元素凝成一片荆棘，$N被划的遍体鳞伤！\n"NOR,who);
                       	who->receive_damage("kee",50);
                      	COMBAT_D->report_status(who);
                        break;
               	}
               	case 4:
                { 
                       	message_vision(HIB"\n四周火元素凝成一道火墙，$N被烧的焦头烂额！\n"NOR,who);
                       	who->receive_damage("kee",50);
                      	COMBAT_D->report_status(who);
                        break;
               	}
               	case 5:
                { 
                       	message_vision(HIB"\n四周一直地动山摇，$N被摇的东倒西歪！\n"NOR,who);
                       	who->receive_damage("kee",50);
                      	COMBAT_D->report_status(who);
                        break;
               	}
	}
    }
  if ( (100*(who->query("kee")))/(who->query("max_kee")) <= 10)
    {
     	message_vision(HIY"$N实在坚持不住了，大叫老君救我。\n"NOR,who);
     	message_vision(HIY"$N眼前袖袍一闪，离开了五行空间。\n"NOR,who);
     	who->delete_temp("wuxing_learn");
     	who->delete_temp("wuxing_learning");
     	who->move("/d/33tian/dadian");
     	who->unconcious();
     	return 1;
    }
  	remove_call_out ("check_hp");
  	call_out ("check_hp", 6+random(5),who);
  	return 1;
  }
int do_lingwu()
{
  	object who = this_player();
  	if( who->query("wuxing_cant") )
  	{
  		message_vision(HIY"你对五行的认识，已经到了你的极限。\n"NOR,who);
  		return 0;
  	}
  	if( !who->query_temp("wuxing_learn") )
  	{
  		message_vision(HIY"没有太上老君的允许，不得私自领悟。\n"NOR,who);
  		return 0;
  	}
  	if( who->query_temp("wuxing_learning") )
  	{
  		message_vision(HIY"你正在领悟。\n"NOR,who);
  		return 0;
  	}
  	message_vision(HIY"$N仔细观察着四周五行元素的规律，慢慢沉浸在了五行的世界里面。\n"NOR,who);
	who->set_temp("wuxing_learning",1);
	call_out("check",6+random(5),who,0);
	return 1;  
}
int check(object who,int k)
{
	if( !who )	
		return 0;
	if(base_name(environment(who)) != "/d/33tian/wuxing")
	{
		message_vision(HIY"$N离开了五行空间，领悟被中断。\n"NOR,who);
		who->delete_temp("wuxing_learning");
		who->delete_temp("wuxing_learn");
		return 0;
	}
	k = k + 1;
	if( k == 1 )	message_vision(HIY"$N喃喃念道:天地万物皆有灵性，分五行。\n"NOR,who);
	if( k == 2 )	message_vision(HIY"$N喃喃念道:所谓五行者，金木水火土，乃宇宙之根本，分化繁衍，遂成大千世界。\n"NOR,who);
	if( k == 3 )	message_vision(HIY"$N喃喃念道:而天地大法，便在于五行之道。五行之道，有相生相克之说。\n"NOR,who);
	if( k == 4 )	message_vision(HIY"$N喃喃念道:相克即金克木、木克土、土克水、水克火、火克金。\n"NOR,who);
	if( k == 5 )	message_vision(HIY"$N喃喃念道:相生即金生水、水生木、木生火、火生土、土生金。\n"NOR,who);
	if( k == 6 )	message_vision(HIY"$N喃喃念道:人言五属魔法必定据此相生相克。此大谬也。\n"NOR,who);
	if( k == 7 )	message_vision(HIY"$N喃喃念道:君不见烈火涸水，洪水决堤乎？此则火亦可克水，水亦可克土。\n"NOR,who);
	if( k == 8 )	message_vision(HIY"$N喃喃念道:拘泥五行相克之论，刻舟求剑耳。五行根本之道，非相克，非相生，而在于相化也。\n"NOR,who);
	if( k == 9 )	message_vision(HIY"$N喃喃念道:以薪火之力，可以沸锅水。然以薪火之力安能沸江湖邪？非火不可克水，势不足矣。\n"NOR,who);
	if( k == 10 )	message_vision(HIY"$N喃喃念道:水火相克在于彼此之势，势不敌则力不逮。力不逮时安奈何？\n"NOR,who);
	if( k == 11 )	message_vision(HIY"$N喃喃念道:惟有变化矣。以强势之火，敌若势之水，则火克水。\n"NOR,who);
	if( k == 12 )	message_vision(HIY"$N喃喃念道:以等势之水火相敌，火恐不逮。倘能化火为等势之土，则可以克水。\n"NOR,who);
	if( k == 13 )	message_vision(HIY"$N喃喃念道:以若势之火，敌强势之水，火必被克。但倘能化火为等势之水，则可以求生。\n"NOR,who);
	if( k == 14 )	message_vision(HIY"$N喃喃念道:万物均有五属灵性，因强弱而分五行。木属之物，并非全无金水火土四性，相较弱耳。\n"NOR,who);
	if( k == 15 )	message_vision(HIY"$N喃喃念道:而其五行属性无时不在变化之中，此则何以沧海为桑田也。\n"NOR,who);
	if( k == 16 )	message_vision(HIY"$N喃喃念道:五行相化，便是以意念力控制某物或自身之五行属性，调整变化，顺应时势也。\n"NOR,who);
	if( k == 17 )	message_vision(HIY"$N喃喃念道:言易行难，若无极强之念力、五行修行之体验，自然无法作到。上古至今，能五行变化者，不过数人而已。\n"NOR,who);
	if( k == 18 )	message_vision(HIY"$N喃喃念道:欲五行相化，必先修五行之意。五行之金木水火土，其根本为‘恒’、‘生’、‘变’、‘亡’、‘容’也。\n"NOR,who);
	if( k == 19 )	message_vision(HIY"$N喃喃念道:即永恒、生长、变化、毁灭、包容五道耳。五行为万物之基，亦为万物之律。\n"NOR,who);
	if( !who->query("wuxing_known") && k > 4 )
	{
		message_vision(HIY"$N冥冥中，似有所悟。\n"NOR,who);
		if( random(who->query("int")) > 20 - random( who->query("lunhui_zhuanshi") ) )
			call_out("finish",6+random(5),who);
		else
			call_out("finish2",6+random(5),who);
		remove_call_out("check");	
		return 1;
	}
	if( who->query("wuxing_known") == 1 && k > 12 )
	{
		message_vision(HIY"$N冥冥中，似有所悟。\n"NOR,who);
		if( random(who->query("int")) > 25 - random( who->query("lunhui_zhuanshi") ) )
			call_out("finish",6+random(5),who);
		else
			call_out("finish2",6+random(5),who);
		remove_call_out("check");	
		return 1;
	}
	if( who->query("wuxing_known") == 2 && k > 18 )
	{
		message_vision(HIY"$N冥冥中，似有所悟。\n"NOR,who);
		if( random(who->query("int")) > 30 - random( who->query("lunhui_zhuanshi") ) )
			call_out("finish",6+random(5),who);
		else
			call_out("finish2",6+random(5),who);
		remove_call_out("check");	
		return 1;
	}
	call_out("check",6+random(5),who,k);
}

int finish(object who)
{
	object downroom = load_object(__DIR__"dadian");
	if(base_name(environment(who)) != "/d/33tian/wuxing")
	{
		message_vision(HIY"$N离开了五行空间，领悟被中断。\n"NOR,who);
		who->delete_temp("wuxing_learning");
		who->delete_temp("wuxing_learn");
		return 0;
	}
	if( !who->query("wuxing_known") )
	{
		message_vision(HIY"$N自言自语：若是能够明辨五行，以相克之力攻敌，自是事半功倍！\n"NOR,who);
		message_vision(HIY"$N不自觉运转镇元神功，五行之力应念而生！\n"NOR,who);
		message_vision(HIY"只见不同属性的光芒不断从$N身上散出，与四周相应元素相互呼应！\n"NOR,who);
		message_vision(HIY"时间慢慢流逝，$N对五行的认识逐渐加深！\n"NOR,who);
		message_vision(HIY"$N一声长啸，身上光芒大盛，各色光芒在$N周围盘旋穿梭！\n"NOR,who);
		message_vision(HIY"过了一会各色光芒慢慢被$N吸纳入体，$N微微一笑，失去了踪影！\n"NOR,who);
		who->set("wuxing_known",1);
		who->delete_temp("wuxing_learn");
     		who->delete_temp("wuxing_learning");
		who->move("/d/33tian/dadian");
		message_vision(HIY"一个耀眼的身影，突然出现在大殿之上！\n"NOR,downroom);
		message("chat",HIC+"\n\n〖"+HIW+"惊天谣传"+HIC+"〗太上老君(taishang laojun)：" + who->name() + "经过不断努力终于领悟了五行的基本道理，学会了"+HIB"[太极五行]"+HIC"！\n\n\n"NOR,users());
		return 1;
	}
	if( who->query("wuxing_known") == 1 )
	{
		message_vision(HIY"$N自言自语：若是能以对手五行之力，激起本身五行，再以本身相克之力攻击。。。\n"NOR,who);
		message_vision(HIY"$N不自觉运转五行心法，感应四周五行元素！\n"NOR,who);
		message_vision(HIY"$N尝试着将四周五行元素吸入体内，再以五行相生之法顺序运转本身五行之力！\n"NOR,who);
		message_vision(HIY"只见$N吸入金元素后，身上发出耀眼的白光！\n"NOR,who);
		message_vision(HIW"$N吸入金元素后，身上发出耀眼的白光！\n"NOR,who);
		message_vision(BLK"$N运转心法将吸入的金元素，转化为体内金之力，并用心法引导冲入本身水之力中，瞬间$N体内水之力爆发，身上光芒转为黯淡！\n"NOR,who);
		message_vision(HIC"$N再运转心法，将这股力量引导折入木之力，$N身上青芒大盛！\n"NOR,who);
		message_vision(HIR"$N再运转心法，将这股力量引导折入火之力，$N身上红芒大盛！\n"NOR,who);
		message_vision(HIY"$N一声清啸，对着五行山挥出一拳，五行山中的金元素竟然被$N这一拳融化了不少！\n"NOR,who);
		message_vision(HIY"$N微微一笑，失去了踪影！\n"NOR,who);
		who->set("wuxing_known",2);
		who->delete_temp("wuxing_learn");
     		who->delete_temp("wuxing_learning");
		who->move("/d/33tian/dadian");
		message_vision(HIY"一个耀眼的身影，突然出现在大殿之上！\n"NOR,downroom);
		message("chat",HIC+"\n\n〖"+HIW+"惊天谣传"+HIC+"〗太上老君(taishang laojun)：" + who->name() + "经过不断努力终于领悟了五行相化的道理，"+HIB"[太极五行]"+HIC"的威力提高了不少！\n\n\n"NOR,users());
		return 1;
	}
	if( who->query("wuxing_known") == 2 )
	{
		message_vision(HIY"$N自言自语：太极生两仪，两仪生四象，万物皆由太极生化而来。\n"NOR,who);
		message_vision(HIY"$N自言自语：五行之中蕴涵天地万物至理，自然与太极密不可分。\n"NOR,who);
		message_vision(HIY"$N自言自语：太极乃本源之力，自然无坚不摧，若是将五行合一。。。\n"NOR,who);
		message_vision(HIY"$N不自觉运转五行心法，以自身为熔炉，试着将五行合一！\n"NOR,who);
		message_vision(HIY"$N以本身土之力，带行其他四行！\n"NOR,who);
		message_vision(HIY"五行真气相生相激，进而阴阳分化，化作两道洪流分行奇经八脉！\n"NOR,who);
		message_vision(HIY"阴阳真气慢慢汇聚于任、督二脉，由动入静。\n"NOR,who);
		message_vision(HIY"下一瞬间，原本就要静止的两道真气，同时冲向$N的生死玄关！\n"NOR,who);
		message_vision(HIY"$N体内真气化作一道长虹，贯穿天地桥梁，天地间的浩然正气，滚滚而来！\n"NOR,who);
		message_vision(HIY"$N再看身前五行大山，只觉一丝一理都与天地之理相合！\n"NOR,who);
		message_vision(HIY"$N有悟于心，却又觉得太极之中似乎还有一层蕴涵！\n"NOR,who);
		message_vision(HIY"$N体内浩然正气突然生出一股力量，$N瞬间失去了踪影！\n"NOR,who);
		who->set("wuxing_known",3);
		who->delete_temp("wuxing_learn");
     		who->delete_temp("wuxing_learning");
		who->move("/d/33tian/dadian");
		message_vision(HIY"一个耀眼的身影，突然出现在大殿之上！\n"NOR,downroom);
		message("chat",HIC+"\n\n〖"+HIW+"惊天谣传"+HIC+"〗太上老君(taishang laojun)：" + who->name() + "经过不断努力终于领悟了五行合一的至理，完全掌握了"+HIB"[太极五行]"+HIC"！\n\n\n"NOR,users());
		return 1;
	}
	return 1;	
}

int finish2(object who)
{
	object downroom = load_object(__DIR__"dadian");
	if(base_name(environment(who)) != "/d/33tian/wuxing")
	{
		message_vision(HIY"$N离开了五行空间，领悟被中断。\n"NOR,who);
		who->delete_temp("wuxing_learning");
		who->delete_temp("wuxing_learn");
		return 0;
	}
	message_vision(HIY"$N运转镇元神功，感应四周五行元素！\n"NOR,who);
	message_vision(HIY"只见不同属性的光芒不断从$N身上散出，与四周相应元素相互呼应！\n"NOR,who);
	message_vision(HIY"时间慢慢流逝，$N对五行的认识逐渐加深！\n"NOR,who);
	message_vision(HIY"突然$N现出痛苦神色，竟是$N无法控制体内五行真气，走火入魔了！\n"NOR,who);
	message_vision(HIY"五行空间中响起太上老君的叹息之声！\n"NOR,who);
	message_vision(HIY"$N眼前袖袍一闪，离开了五行空间。\n"NOR,who);
	who->set("wuxing_cant",1);
	who->delete_temp("wuxing_learn");
     	who->delete_temp("wuxing_learning");
     	if( !who->query("wuxing_known") )
		message("chat",HIC+"\n\n〖"+HIW+"惊天谣传"+HIC+"〗太上老君(taishang laojun)：" + who->name() + "机缘不够，无法领会五行至理，终不能学会"+HIB"[太极五行]"+HIC"，真是可惜啊！\n\n\n"NOR,users());
	else
		message("chat",HIC+"\n\n〖"+HIW+"惊天谣传"+HIC+"〗太上老君(taishang laojun)：" + who->name() + "机缘不够，无法领会更深的五行之理，终不能完全掌握"+HIB"[太极五行]"+HIC"，真是可惜啊！\n\n\n"NOR,users());
	message_vision(HIY"一个耀眼的身影，突然出现在大殿之上！\n"NOR,downroom);
	who->move("/d/33tian/dadian");
	who->unconcious();
	return 1;	
}