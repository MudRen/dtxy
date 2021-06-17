// writted by mind
#include <ansi.h>
inherit ROOM;
void create()
{
        set("short", "冰窖");
        set("long", @LONG
这是西梁女儿国的一个巨大冰窖，原来用来为皇家储藏珍贵食物的，
现在虽然已经荒废，但是里面的冰块依然堆得满满的，四周墙壁已经结
了厚厚的冰。无数冰凌闪着刺眼的光，这么个寒冷的地方，寒气已经透
不出去，积年日久，已经极其寒冷，里面恐怕半个时辰都呆不了。
LONG
        );
        set("exits", ([ 
  "out" : "/d/qujing/nuerguo/shanpo",
]));
        set("objects", ([
                
       ]) );
        
        setup();
        
}

void init ()
{
  add_action ("do_around","around");
  add_action("do_yanjiu", "xiulian");
}

int do_around ()
{
  object me = this_player ();
  if( (string)me->query("family/family_name")!="三界散仙" && !wizardp(me) )
                return notify_fail("你觉得这冰窖异常的寒冷。\n");
  message_vision ("$N浑身哆嗦着，抵御周围的寒气。\n",me);  
  if(!me->query("m_success/冰魄刀"))
  {
    message_vision ("$N的衣服似乎也开始结冰！\n",me);
    call_out("fainting",5,me);  
    return 1;
  }
  if(!me->query_skill("bingpo-hand", 1)){
  message_vision("$N使劲顿脚舞手，不停地运内息抵御寒气，居然悟出了一套拳法。\n",me);
  me->set_skill("bingpo-hand",1);}
  return 1;
}


void fainting (object me)
{
        message_vision("突然$N嘴唇发青发紫，脸色苍白，一个踉跄倒在地上。。。\n", me);
        me->set("m_success/冰魄刀",1);
        me->unconcious();
}

int do_yanjiu()
{       
        object me=this_player();
        int sen_cost, kee_cost, force_cost, gain;
	if( (string)me->query("family/family_name")!="三界散仙" && !wizardp(me) )
                return notify_fail("你觉得这冰窖异常的寒冷。\n");
        if( me->is_busy() )
                return notify_fail("你忙的很，哪有功夫修炼！\n");
        if( me->is_fighting() )
                return notify_fail("现学现卖已来不及了！\n");
        if( (int)me->query_skill("literate", 1) < 40)
                return notify_fail("你文化太低！\n");
        if( (int)me->query_skill("unarmed", 1) < 40)
                return notify_fail("你还是先学基本拳脚功夫吧。\n");
        if( (int)me->query_skill("bingpo-hand", 1) >= 100)
                return notify_fail("你感觉冰窖已经不适合修炼了。\n");
        if( (int)me->query("max_force") < 400)
                return notify_fail("你底气不足，练不了。\n");
	if(!me->query("m_success/冰魄刀"))
	{
		message_vision ("$N的衣服似乎也开始结冰！\n",me);
		call_out("fainting",5,me);  
		return 1;
	}
	if( me->query("icefire/ice") == 1 )
	{
		sen_cost = 45;
	        if( (int)me->query("sen") < sen_cost )
	                return notify_fail("你现在头晕脑胀，该休息休息了。\n");
	
	        kee_cost = 45;
	        if( (int)me->query("kee") < kee_cost )
	                return notify_fail("你现在浑身无力，该休息休息了。\n");
	
	        force_cost = 20;
	        if( (int)me->query("force") < force_cost )
	                return notify_fail("你现在已提不起气了，该休息休息了。\n");
	
	        me->receive_damage("sen", sen_cost);
	        me->receive_damage("kee", kee_cost);
	        me->add("force", - force_cost);
	
	        gain = (int)me->query_int()/2 + (int)me->query_con()/2 + 1 + random(10);
	
	        me->improve_skill("butian-force", gain);
	        write("你感受着寒冰的力量，对『寒冰心法』有所了解。\n");
	        write("你试着借助冰窖的力量凝结出冰魄刀。\n");
	        me->start_busy(3);
	        if( random(me->query("kar")) < 14 )
	        {
			message_vision ("$N的衣服似乎也开始结冰！\n",me);
			call_out("fainting",2,me);  
			return 1;
		}
		if( random(me->query("kar")) > 24 )
		{
			message_vision (HIW"$N鼓动真气，左手上开始结出细小的冰凌！\n"NOR,me);
			message_vision (HIW"$N继续运转寒冰心法，终于形成了冰魄刀！\n"NOR,me);
			if( me->query("icefire/fire") == 2 )//fire已经完成
			{
				me->start_busy(15);
				me->delete("icefire");
				if( random(me->query("int")) > 20 - random( me->query("lunhui_zhuanshi") ) )
					call_out("finish1",10,me);
				else
					call_out("finish2",10,me);
			}
			else
			{
				message_vision (HIW"$N一激动，不小心磕在了冰块上！\n"NOR,me);
				me->set("icefire/ice",2);
				call_out("fainting",2,me);  
			}
			return 1;
		}
	}
	else if( me->query("icefire/fire") == 3 )
	{
		sen_cost = 45;
	        if( (int)me->query("sen") < sen_cost )
	                return notify_fail("你现在头晕脑胀，该休息休息了。\n");
	
	        kee_cost = 45;
	        if( (int)me->query("kee") < kee_cost )
	                return notify_fail("你现在浑身无力，该休息休息了。\n");
	
	        force_cost = 20;
	        if( (int)me->query("force") < force_cost )
	                return notify_fail("你现在已提不起气了，该休息休息了。\n");
	
	        me->receive_damage("sen", sen_cost);
	        me->receive_damage("kee", kee_cost);
	        me->add("force", - force_cost);
	
	        gain = (int)me->query_int()/2 + (int)me->query_con()/2 + 1 + random(10);
	
	        me->improve_skill("butian-force", gain);
	        write("你运起炎阳心法对抗着寒冰的力量，对『炎阳心法』的领悟加深了。\n");
	        write("你试着在冰窖中凝练出火焰刀。\n");
	        me->start_busy(3);
	        if( random(me->query("kar")) < 16 )
	        {
			message_vision ("$N的衣服似乎也开始结冰！\n",me);
			call_out("fainting",2,me);  
			return 1;
		}
		if( random(me->query("kar")) > 30 - random( me->query("lunhui_zhuanshi") ) )
		{
			message_vision (HIR"$N鼓动真气，体内真气渐渐变热！\n"NOR,me);
			message_vision (HIR"$N继续运转炎阳心法，冰窖内的温度慢慢升高，冰块开始融化，忽的火焰刀在你右手燃起！\n"NOR,me);
			if( me->query("icefire/ice") == 4 )//ice已经完成
			{
				me->start_busy(15);
				me->delete("icefire");
				if( random(me->query("int")) > 25 )
					call_out("finish1",10,me);
				else
					call_out("finish2",10,me);
			}
			else
			{
				message_vision (HIW"$N一激动，不小心磕在了冰块上！\n"NOR,me);
				me->set("icefire/fire",4);
				call_out("fainting",2,me);  
			}
			return 1;
		}
	}
	else
	{
	        sen_cost = 45 - (int)me->query_int();
		if (sen_cost<0) sen_cost=20;
	        if( (int)me->query("sen") < sen_cost )
	                return notify_fail("你现在头晕脑胀，该休息休息了。\n");
	
	        kee_cost = 45 - (int)me->query_con();
		if (kee_cost<20) kee_cost=20;
	        if( (int)me->query("kee") < kee_cost )
	                return notify_fail("你现在浑身无力，该休息休息了。\n");
	
	        force_cost = 20;
	        if( (int)me->query("force") < force_cost )
	                return notify_fail("你现在已提不起气了，该休息休息了。\n");
	
	        me->receive_damage("sen", sen_cost);
	        me->receive_damage("kee", kee_cost);
	        me->add("force", - force_cost);
	
	        gain = (int)me->query("int")/2 + (int)me->query("con")/2 + 1 + random(10);
	
	        me->improve_skill("bingpo-hand", gain);
	
	        write("你施展拳脚，催动内息，对『冰魄刀』又有所了解。\n");
	}

        tell_room( environment(me), me->name() + "身法轻灵，手脚怪异地舞动。\n", ({me}));

        return 1;
}

void finish1( object me )
{
	me->add("icefire_known",1);
	if( me->query("icefire_known") == 1 )
	{
		message_vision(HIW"$N伸手抚摸冰魄刀，凉意入骨，内心出奇的平静。\n" NOR,me);
		message_vision(HIW"$N缓缓收起寒冰心法！\n" NOR,me);
		message("chat",HIC+"\n\n〖"+HIW+"惊天谣传"+HIC+"〗鬼谷子(gui guzi)：" + me->name() + "勇闯冰窖火窟，领悟了炎阳寒冰心法，悟出了散仙绝学["+HIW"冰"+HIR"火"+HIY+"诀"+HIC"]！\n\n\n"NOR,users());
	}
	else
	{
		message_vision(HIR"$N伸手抚摸那股跃动的火焰，内心出奇的平静。\n" NOR,me);
		message_vision(HIR"$N缓缓收起炎阳心法！\n" NOR,me);
		message("chat",HIC+"\n\n〖"+HIW+"惊天谣传"+HIC+"〗鬼谷子(gui guzi)：" + me->name() + "再闯冰窖火窟，将散仙绝学["+HIW"冰"+HIR"火"+HIY+"诀"+HIC"]练到了极至！\n\n\n"NOR,users());
	}
	return ;
}

void finish2( object me )
{
	me->set("icefire_cant",1);
	if( !me->query("icefire_known") )
	{
		message_vision(HIC"$N丹田内真气异常寒冷，物极而反，突然一股炽热真气自丹田内部涌出。\n" NOR,me);
		message_vision(HIC"$N手上冰魄刀瞬间融化了，$N好不容易将内力平息，再找不到先前的感觉！\n" NOR,me);
		message("chat",HIC+"\n\n〖"+HIW+"惊天谣传"+HIC+"〗鬼谷子(gui guzi)：" + me->name() + "勇闯冰窖火窟，可惜未能领悟寒冰心法，终与散仙绝学["+HIW"冰"+HIR"火"+HIY+"诀"+HIC"]无缘！\n\n\n"NOR,users());
	}
	else
	{
		message_vision(HIC"$N丹田内真气炎热异常，物极而反，突然一股冰寒真气自丹田内部涌出。\n" NOR,me);
		message_vision(HIC"$N手上火焰刀瞬间熄灭了，$N好不容易将内力平息，再找不到先前的感觉！\n" NOR,me);
		message("chat",HIC+"\n\n〖"+HIW+"惊天谣传"+HIC+"〗鬼谷子(gui guzi)：" + me->name() + "再闯冰窖火窟，可惜未能将炎阳寒冰心法融会贯通，无法将散仙绝学["+HIW"冰"+HIR"火"+HIY+"诀"+HIC"]练到极至！\n\n\n"NOR,users());
	}
	return ;
}