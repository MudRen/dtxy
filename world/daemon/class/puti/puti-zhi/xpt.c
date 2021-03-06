/*
【菩提指】这套指法为菩提祖师所创，时间上在劫难指之后。当年菩提
祖师在佛祖门下时与诸多同门不和，后赴方寸山另立门派。菩提祖师对
阿难珈叶在佛祖面前逢承拍马之行径一向不屑，对二人从佛祖拈花微笑
中悟出的劫难指当然是嗤之以鼻。菩提指以菩提之名为名便是笑话二人
拍马之意。

　　菩提本无树，明镜亦非台。
　　本来无一物，何处惹尘埃。
*/
#include <ansi.h>
inherit SSERVER;

int perform(object me, object target)
{
  object weapon;
  int damage,enhance,damage1,dp;   
  string msg,str;
  int i;
  int cd = 5;
  if( !target ) target = offensive_target(me);
        if( !target
        ||      !target->is_character()
        ||      target->is_corpse()
        ||      target==me)
                return notify_fail("你要对谁施展笑菩提？\n");
        if(!wizardp(me) && me->query("family/family_name") != "方寸山三星洞")
                return notify_fail("你不是方寸山三星洞弟子！\n");
        if(!me->is_fighting(target))
                return notify_fail("你没有在战斗中！\n");
        if((int)me->query("force") < 1000 )
                return notify_fail("你的内力不够！\n");
        if((int)me->query("kee") < 600 )
                return notify_fail("你的气血不足，没法子施用外功！\n");
        if(me->query_skill("wuxiangforce", 1) < 120)
                return notify_fail("你的无相神功等级太低了！\n");
        if(me->query_skill("unarmed", 1) < 120)
                return notify_fail("你的拳脚功夫不行！\n");
        if(me->query_skill("puti-zhi", 1) < 120)
                return notify_fail("你的菩提指等级太低了！\n");
        if( me->query("lunhui_zhuanshi") )
		cd = 4;
        if( time()-(int)me->query_temp("xpt_end") < cd )
                return notify_fail("绝招用多了，就不灵了！\n");
        me->set_temp("xpt_end",time());
        enhance = me->query_skill("wuxiangforce", 1);
        damage1 = me->query_skill("puti-zhi", 1)/3 + me->query_skill("unarmed", 1)/2;
        dp = target->query_temp("apply/armor_vs_force")/2;
        message_vision(HIC"\n$N突然立定，右手食指扣住拇指作"+HIY"「佛祖拈花」"+HIC"状。\n"NOR,me,target);
        if( random(enhance) > target->query_skill("dodge",1)/5 )
        {
        	me->add("force", -damage1/6);
        	message_vision(YEL"\n$n看不破$N的心思，稍一犹豫。\n"NOR,me,target);
          	message_vision(HIC"\n$N面带微笑右手双指轻轻弹出一缕罡气，直指$n。\n"NOR,me,target);
        	message_vision(HIR"\n$n这一愣神，被罡气刺穿了右臂！\n"NOR,me,target);
        	damage=damage1 + random(damage1-dp);
        	if( damage < damage1 ) damage = damage1;
		target->receive_damage("kee",damage,me);
		target->receive_wound("kee",damage/3,me);
		COMBAT_D->report_status(target);
		if( random(enhance) > target->query_skill("dodge",1)/4 )
		{
			me->add("force", -damage1/5);
			message_vision(HIC"\n$n疼的打了个激灵，慌忙左闪！\n"NOR,me,target);
			message_vision(HIC"\n但闻哧哧两声，$n脸色突变，$N却悠闲自在，并无动过手的迹象！\n"NOR,me,target);
			message_vision(HIR"\n却是$n被$N双手拇指捺出的两股罡气击中了胸部！\n"NOR,me,target);
			damage=damage1 + random(damage1*2-dp);
			if( damage < damage1 ) damage = damage1;
			target->receive_damage("kee",damage,me);
			target->receive_wound("kee",damage/3,me);
			COMBAT_D->report_status(target);
			if( random(enhance) > target->query_skill("dodge",1)/3 )
			{
				me->add("force", -damage1/4);
				message_vision(HIC"\n$n双手捂胸，疼的脸色发青！\n"NOR,me,target);
				message_vision(HIC"\n$N负手而立，张口喝出一道浑厚罡气，直击$n头部！\n"NOR,me,target);
				message_vision(HIR"\n$n实在无力闪避，被罡气打得两耳轰鸣，差点精神错乱！\n"NOR,me,target);
				damage=damage1 + random(damage1*3-dp);
				if( damage < damage1 ) damage = damage1;
				target->receive_damage("kee",damage,me);
				target->receive_wound("kee",damage/3,me);
				target->receive_wound("sen",damage/3,me);
				COMBAT_D->report_status(target);	
				COMBAT_D->report_sen_status(target);	
			}
		}
        }
        else
        {
		message_vision(HIY"\n$n“扑哧”笑出声来：菩提老道何时也作拈花状？！\n"NOR,me,target);
		me->add("force", -100);
	}
	//me->start_busy(1+random(2));
	return 1;
}