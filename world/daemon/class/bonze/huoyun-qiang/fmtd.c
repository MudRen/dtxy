//大藏经、金刚般若婆罗密经、大方广佛华严经、观无量寿佛经、随念三宝经、三十因果经、四十二章经、妙法莲花经、地藏菩萨本愿经
#include <ansi.h>

inherit SSERVER;
string* fojing = ({
	HIB"大藏经"NOR,
	HIY"金刚般若婆罗密经"NOR,
	HIM"大方广佛华严经"NOR,
	WHT"观无量寿佛经"NOR,
	RED"随念三宝经"NOR,
	HIG"三十因果经"NOR,
	BLU"四十二章经"NOR,
	HIW"妙法莲花经"NOR,
	HIR"地藏菩萨本愿经"NOR,
});
string* zhenyan = ({"唵","嘛","呢","叭","咪","吽",});
int perform(object me, object target)
{
        
	object weapon;
   	int damage,jiali;
	int enhance,damage1, mypot,tapot;
	int weapon_damage = me->query_temp("apply/damage");
	string str,xuename,dodge_skill;
        int cd = 10;
        if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      target->is_corpse()
        ||      target==me)
                return notify_fail("你要对谁施展这「佛魔同道」奇功？\n");

        if(!me->is_fighting(target))
                return notify_fail("「佛魔同道」只能在战斗中使用！\n");

        if((int)me->query("max_force") < 1000 )
                return notify_fail("你的内力不够！\n");
      	if( !wizardp(me) && me->query("family/family_name") != "南海普陀山" )
                return notify_fail("你是哪儿偷学来的武功！\n");

        if((int)me->query("force") < 1500 )
                return notify_fail("你的内力不足！\n");

        if((int)me->query("sen") < 500 )
                return notify_fail("你的精神不足，没法子施用外功！\n");
	if( !me->query("fmtd_known") )
		return notify_fail("你还没有领悟佛魔同道的奇功！\n");
	enhance=(int)me->query_skill("huoyun-qiang",1);

        if( enhance < 200 )
                return notify_fail("你的枪法级别还不够，使用这一招会有困难！\n");
        damage=(int)me->query_skill("lotusforce",1);
        if( damage < 200 )
                return notify_fail("你的心法级别还不够，使用这一招会有困难！\n");
	jiali = me->query("force_factor")+1;
	
	if( me->query("lunhui_zhuanshi") > 1 )
		cd -= me->query("lunhui_zhuanshi") - 1;
        if( time()-(int)me->query_temp("fmtd_end") < cd )
                return notify_fail("你现在内息不顺！\n");
	mypot = (int)me->query("combat_exp")/10000;
	tapot = (int)target->query("combat_exp")/15000;
       	weapon = me->query_temp("weapon");
       	dodge_skill = target->query_skill_mapped("dodge");
	if( !dodge_skill ) dodge_skill = "dodge";
       	message_vision(HIB"\n$N将"+weapon->name()+NOR+HIB"一摆，以佛门内功为根基，施展出「"+HIR"火云枪法"+HIB"」。\n"NOR,me,target);
       	if( target->query("class") ==  "yaomo" )
       		message_vision(RED"\n$n见状，大吃一惊：好贼秃，竟然偷练我圣门绝学！\n"NOR,me,target);
       	else
       		message_vision(RED"\n$n面色一变：想不到堂堂南海普陀，竟然偷练魔功！\n"NOR,me,target);
       	xuename = fojing[random(sizeof(fojing))];
       	message_vision(CYN"\n$N法像庄严，轻声禅唱，天地立时变得祥和宁静。\n"NOR,me);
       	message_vision(CYN"$n侧耳倾听，$N颂念的正是"+xuename+CYN"。\n"NOR,me,target);
       	message_vision(HIC"$N口宣佛号，指天地而问：何谓佛魔之分？！$n不由低头沉思。\n"NOR,me,target);
       	xuename = zhenyan[random(sizeof(zhenyan))];
       	message_vision(RED"\n$N挥动"+weapon->name()+NOR+RED"于枪尖上结出一个斗大的真言："+BLINK+HIY+xuename+NOR+RED"！\n"NOR,me,target);
       	message_vision(RED"\n$N低宣佛号，真言径直向$n印去！\n"NOR,me,target);
        if( random( mypot ) > tapot/4 ) 
	{       
             	damage1 = damage + jiali;
             	me->add("force",-damage1/4);
             	damage1 = damage1 + random(enhance/3);
             	message_vision(HIR"\n结果$n被真言实实印在前胸，波的喷出一口鲜血！\n"NOR,me,target);
             	target->receive_damage("kee",damage1,me);
	        target->receive_wound("kee",damage1/3,me);
	 	COMBAT_D->report_status(target);
	}
	else
	{
		me->add("force",-60);
         	message_vision(YEL+SKILL_D(dodge_skill)->query_dodge_msg(target, 1)+NOR, me, target);
	}
	xuename = zhenyan[random(sizeof(zhenyan))];
	message_vision(CYN"\n紧接着$N大吼一声，"+weapon->name()+NOR+CYN"连挥如一幅泼墨山水，纵横倚斜，寥寥数笔挥就一个斗大的真言："+BLINK+HIR+xuename+NOR+CYN"！\n"NOR,me,target);
	message_vision(RED"\n真言字体金芒刺眼，四周却是烈焰熊熊，呼啸着扑向$n！\n"NOR,me,target);
	if( random(mypot) > tapot/3 )
	{
		damage1 = damage + jiali / 2;
             	me->add("force",-damage1/5);
             	damage1 = damage1 + random(enhance/3);
             	message_vision(HIR"\n结果$n被真言实实印在前胸，波的喷出一口鲜血！\n"NOR,me,target);
	        target->receive_damage("kee",damage1,me);
	        target->receive_wound("kee",damage1/3,me);
	 	COMBAT_D->report_status(target);
	 	damage1 = enhance + jiali / 2;
	 	me->add("force",-damage1/5);
	 	damage1 = damage1 + random(damage/3);
	 	target->receive_damage("kee",damage1,me);
	        target->receive_wound("kee",damage1/3,me);
	 	message_vision(HIR"\n紧跟着烈焰席卷而上将$n烧得焦头烂额！\n"NOR,me,target);
	 	COMBAT_D->report_status(target);
	}
	else if( random(mypot) > tapot/4 )
	{
		damage1 = damage + jiali;
             	me->add("force",-damage1/4);
             	damage1 = damage1 + random(enhance/3);
		message_vision(YEL"\n$n慌忙运功护体，将烈焰拒于三尺之外！\n"NOR,me,target);
		message_vision(HIY"不想真言内蕴的佛门真力极为集中，刺破了$n的护体真气！\n"NOR,me,target);
		target->receive_damage("kee",damage1,me);
	        target->receive_wound("kee",damage1/3,me);
	 	COMBAT_D->report_status(target);
	}
	else if( random(mypot) > tapot/5 )
	{
		message_vision(YEL"\n$n识得厉害，劈出一道真气，将真言逼住！\n"NOR,me,target);
		message_vision(HIR"不想真言内蕴的佛门真力突然迸发，烈焰暴涨，将$n烧得焦头烂额！\n"NOR,me,target);
		damage1 = enhance + jiali;
             	me->add("force",-damage1/4);
             	damage1 = damage1 + random(damage/3);
             	target->receive_damage("kee",damage1,me);
	        target->receive_wound("kee",damage1/3,me);
	 	COMBAT_D->report_status(target);
	}
	else
	{
		me->add("force",-100);
         	message_vision(YEL+SKILL_D(dodge_skill)->query_dodge_msg(target, 1)+NOR, me, target);
	}
	if( me->query("fmtd_known") > 1 )
	{
		xuename = fojing[random(sizeof(fojing))];
		message_vision(HIC"\n$N梵唱又起，正是"+xuename+HIC"！\n"NOR,me,target);
		message_vision(HIC"\n"+weapon->name()+NOR+HIC"上绽放出耀眼的光芒。\n"NOR,me,target);
		message_vision(HIC"那光芒起先红金相间，待到后来，红金相融无间，再分辨不出本来颜色。\n"NOR,me,target);
		message_vision(HIC"$N口念六字真言，音生枪动，洒出朵朵枪花。\n"NOR,me,target);
		message_vision(HIC"枪花首尾相连将$n困在当中，$n仔细一看，朵朵枪花尽是佛家真言。\n"NOR,me,target);
		message_vision(WHT"\n$N低吟“阿弥陀佛！”佛家真言应声攻向$n！\n"NOR,me,target);
		if( random(mypot+tapot) > tapot/2 )
		{
			damage1 = damage + jiali + enhance;
			me->add("force",-damage1/4);
			damage1 = damage1 * 2 + random(damage1/3);
			message_vision(HIR"结果$n被这包含佛魔无上真力的真言击中，像滩软泥般塌了下去！\n"NOR,me,target);
	 		target->receive_damage("kee",damage1,me);
	        	target->receive_wound("kee",damage1/2,me);
	 		COMBAT_D->report_status(target);
		}
		else
		{
			me->add("force",-120);
	         	message_vision(YEL+SKILL_D(dodge_skill)->query_dodge_msg(target, 1)+NOR, me, target);
		}
	}
	//me->start_busy(2);       
	me->receive_damage("sen", 150);
	me->set_temp("fmtd_end",time());
        return 1;
}
