//琴音清韵
//2006 修正
//2006 增加解密攻击
 
#include <ansi.h>

inherit F_DBASE;
inherit SSERVER;

string *zui_miaoshu= ({
HIW"昵昵儿女语，恩怨相尔汝。\n"+
HIR+"琴声显得轻柔细碎 ，音调缠绵宛转，$N"+HIR+"不知不觉收到了影响。\n"NOR,
HIB"划然变轩昂，勇士赴敌场。\n"+
HIR+"刹那间，琴声变得激昂高亢，气势磅礴，威武雄壮，这又把$N"+HIR+"带进了一个完全不同的境界。\n"NOR,
HIM"浮云柳絮无根蒂，天地阔远任飞扬。\n"+
HIR+"声音又转成了舒缓、悠扬，好象那白云悠然于碧空，$N"+HIR+"竟然忘记了自己还在战斗中。\n"NOR,
HIY"喧啾百鸟群，忽见孤凤凰。\n"+
HIR+"猛然间$N"+HIR+"看见似乎有一只高贵的凤凰引颈长鸣，鸣声谐和、清亮。\n"NOR,
HIG"跻攀分寸不可上，失势一落千丈强。\n"+
HIR+"$N"+HIR+"恍恍忽忽往悬崖峭壁上一层一层地往陡险的高峰攀登。\n"NOR,
});

string *shoufa_msg = ({"抹","挑","勾","剔","撇","托","敌","打"});
string *yun_msg = ({"宫","商","角","徵","羽"});

int perform(object me, object target)
{
        object weapon;
        int skill;
        string msg;
        
        if(me->query_temp("BAIFA_perform")) 
                return notify_fail("你已经使出「琴音清韵」了！\n");
        if( time()-(int)me->query_temp("BAIFA_end") < 10 )
                return notify_fail("绝招用多就不灵了！\n");
        
        if((int)me->query("max_force") <1000 )
                return notify_fail("你的内力不够！\n");

        if((int)me->query("force") < 1000 )
                return notify_fail("你的内力不足！\n");

        if((int)me->query("sen") <500 )
                return notify_fail("你的精神不足，没法子施用外功！\n");

        if((int)me->query_skill("chixin-jian",1) <120)
                return notify_fail("你的痴心剑级别还不够施展这一招琴音清韵!!\n");
        if((int)me->query_skill("yueying-wubu",1) <120)
                return notify_fail("你的月影舞步等级不够!!\n");
        if((int)me->query_skill("qin",1) <120)
                return notify_fail("你的琴艺等级不够!!\n");
        if (!present("wuxian qin", me) && !me->is_manmade_npc())
                return notify_fail("「琴音清韵」必须有琴配合才能使用。\n");
        if(!wizardp(me) && me->query("family/family_name") != "盘丝洞" )
                return notify_fail("你不是盘丝洞门人,琴艺早已生疏!!\n");
        
        weapon=me->query_temp("weapon");
        if(me->is_fighting())
        {
        	target = offensive_target(me);
     		msg = HIM  "$N右手持剑应敌，左手取琴环抱，轻轻拨动琴弦，竟是琴艺中失传已久的绝学－－";
     		msg = msg + "\n"YEL"             『琴音"HIC"清韵』";
		msg = msg + "\n"HIW"－－只见$N琴剑合一，漫天剑气琴音氤氲般卷向$n！\n\n" NOR;
    		message_vision(msg, me,target);
     	}
     	else
     	{
     		msg = HIM  "$N盘膝坐在地上，右手持剑，左手抚琴，轻轻弹出琴艺中失传已久的绝学";
     		msg = msg + YEL"『琴音"HIC"清韵』"+HIM"！！！\n"NOR;
		message_vision(msg, me);
	}
        skill = me->query_skill("qin",1);
        me->set_temp("BAIFA_perform", 1);
        call_out("checking", 2, me);
        me->start_call_out( (: call_other, __FILE__, "remove_effect", me :), skill);
        me->add("force", -200);
        return 1;
}
void checking(object me)
{

	object weapon,target;
	int damage,flag = 0;
	string str;
	weapon = me->query_temp("weapon");
	
        if( me->query_temp("BAIFA_perform")  ) 
        {
           	if (!present("wuxian qin", me) && !me->is_manmade_npc() ) 
           	{
                	tell_object(me, "\n你的琴丢了，无法继续弹奏！\n" NOR);
                	me->delete_temp("BAIFA_perform");
			me->set_temp("BAIFA_end",time());
                	return;
           	}
           	else if ( (int)me->query("force") < 1000  ) 
           	{
                	tell_object(me, "\n你的内力后继不足，难以持续「琴音清韵」的威力！\n" );
			me->delete_temp("BAIFA_perform");
			me->set_temp("BAIFA_end",time());
                	return;
           	}
           	else if ( (int)me->query("sen") < 500  ) 
           	{
                	tell_object(me, "\n你的精神太差，无法继续弹奏！\n" );
			me->delete_temp("BAIFA_perform");
			me->set_temp("BAIFA_end",time());
                	return;
           	}
	   	else 
	   	{
	   		//if( me->is_fighting() && me->query("qingyun_known") )
	   		if( me->is_fighting() )
	   		{
	   			target = offensive_target(me);
	   			if( objectp(target) && present(target->query("id"), environment(me)) )
	   			{
	   				/*message_vision(HIM"\n$N轻"+shoufa_msg[random(sizeof(shoufa_msg))]+"琴弦，淡淡琴韵中迸出一个尖锐的"+yun_msg[random(sizeof(yun_msg))]+"音！\n"NOR, me,target);
	   				if( random(me->query_skill("qin",1)) > target->query_skill("force",1)/3 )//第一段；伤害气血
	   				{
	   					message_vision(HIR"$N一个不慎，被琴音刺破了护身真气！\n"NOR, target);
	   					damage = me->query_skill("qin",1)+random(me->query_skill("jiuyin-xinjing",1))-random(target->query_skill("force",1));
	   					if( damage < 1 ) damage = 1+random(me->query_skill("qin",1))/3;
	   					target->receive_damage("kee",damage,me);
	   					target->receive_wound("kee",damage/2,me);
	   					me->add("force",-damage/10);
	   					COMBAT_D->report_status(target);
	   					flag = 1;
	   				}
	   				if( random(me->query_skill("qin",1)) > target->query_skill("spells",1)/3 && me->query("qingyun_known") > 1 )//第二段；伤害精神
	   				{
	   					if( !target->is_busy() ) target->start_busy(random(2));
	   					message_vision(HIR"琴音入耳，$N只觉得耳膜如被针刺，头疼欲裂！\n"NOR, target);
	   					damage = me->query_skill("qin",1)+random(me->query_skill("pansi-dafa",1))-random(target->query_skill("spells",1));
	   					if( damage < 1 ) damage = 1+random(me->query_skill("qin",1))/3;
	   					target->receive_wound("sen",damage,me);
	   					me->add("force",-damage/10);
	   					COMBAT_D->report_sen_status(target);
	   					flag = 1;
	   				}
	   				if( !flag )
	   					message_vision(YEL"$N修为深厚，竟然不被琴音侵扰！！！\n"NOR, target);
	   				*/
	   				message_vision(zui_miaoshu[random(sizeof(zui_miaoshu))], target, me);
	   				if( random(me->query_skill("qin",1)) > target->query_skill("spells",1)/3 )
	   				{
	   					message_vision(HIR"琴音入耳，$N宛如身临其境，不知不觉中乱了思绪！\n"NOR, target);
		   				damage = me->query_skill("qin",1)+random(me->query_skill("pansi-dafa",1))-random(target->query_skill("spells",1));
		   				if( damage < 1 ) damage = 1+random(me->query_skill("qin",1))/3;
		   				target->receive_wound("sen",damage,me);
		   				me->add("force",-damage/10);
		   				COMBAT_D->report_sen_status(target);
				   		if( (target->query("eff_sen") < 0 || !living(target)) && !random(5) )  
					        {
							str=target->name()+HIM"被"+me->name()+HIM+"奏出的"+NOR+HIW+"『蚀魂曲』"+HIM+"迷死了！"NOR;
                         				message("channel:rumor",HIM"【空穴来风】某人："+str+"\n"NOR,users());
						}
	   				}
	   				else
	   					message_vision(YEL"$N修为深厚，竟然不被琴音侵扰！！！\n"NOR, target);
	   			}
	   		}
	   		call_out("checking", 2+random(2), me, target);
	   	}
	}
	else return;
}  



void remove_effect(object me)
{       
	if ( me->query_temp("BAIFA_perform") ) {
        message_vision(HIC"$N手一挥，指尖轻轻滑过琴弦，琴音叮叮咚咚，半响后天地间只余袅袅清韵。\n"NOR, me);
        me->delete_temp("BAIFA_perform");
        me->set_temp("BAIFA_end",time());
         }
}
