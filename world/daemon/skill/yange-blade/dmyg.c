
//vikee 
//damoyange.c you can add it to the directory /daemon/skill/yange-blade/
#include <ansi.h>
#include <combat.h>
inherit SSERVER;
void damoyange_ok(object);
 
int perform(object me, object target)
{
        object weapon,weapon1;
        object* all = all_inventory(me);
        int ap,dp,damage;   
        string str;     
        if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      target->is_corpse()
        ||      target==me)
                return notify_fail("你要对谁施展这一招「大漠雁歌」？\n");
         if( !wizardp(me) && me->query("family/family_name") != "五庄观" )
                return notify_fail("你是哪儿偷学来的武功，也想用「大漠雁歌」?\n");

        if(!me->is_fighting(target))
                return notify_fail("「大漠雁歌」只能在战斗中使用！\n");

        if((int)me->query("max_force") < 1500 )
                return notify_fail("你的内力不够！\n");

	if((int)me->query("force") < 1500 )
		return notify_fail("你的内力不足！\n");

        if((int)me->query("sen") < 500 )
                return notify_fail("你的精神不足，没法子施用外功！\n");
	all = filter(all, (: $1->query("music/type") == "xiao" :) );
	if( !sizeof(all) )
                return notify_fail("你忘记带萧了！\n");
        if((int)me->query_skill("yange-blade", 1) < 180)
                return notify_fail("你的雁歌刀法级别还不够，使用这一招会有困难！\n");
        if((int)me->query_skill("zhenyuan-force", 1) < 180)
                return notify_fail("你的雁歌刀法级别还不够，使用这一招会有困难！\n");
        if((int)me->query_skill("zouxiao", 1) < 180)
                return notify_fail("你的吹箫之技别还不够，使用这一招会有困难！\n");      
        if((int)me->query_skill("xiaofeng-sword", 1) < 180)
                return notify_fail("你的晓风残月剑级别还不够，使用这一招会有困难！\n");      
        //if (me->query_skill_mapped("force")!="zhenyuan-force")
        //        return notify_fail("大漠雁歌必须配合镇元神功才能使用。\n");
        if (me->query_skill_mapped("sword")!="xiaofeng-sword")
                return notify_fail("大漠雁歌必须配合晓风残月剑才能使用。\n");
        if( me->is_busy() )
		return notify_fail("你正忙着呢，哪里有表演的功夫。\n");
 	if( target->is_busy() )
		return notify_fail("对方正忙着呢，没有必要费心表演。\n");
	weapon = all[0];
	weapon1 = me->query_temp("weapon");
	ap = me->query_skill("blade")/2 + me->query_skill("zouxiao",1);
	dp = target->query_skill("dodge")/3 + target->query_skill("force",1);
	message_vision(HIY"\n激战中$N突然全力劈出一刀，将$n逼退数步！\n"NOR,me,target);	
	me->set_temp("dmyg",1);
	COMBAT_D->do_attack(me,target, weapon1);
	me->delete_temp("dmyg");
	weapon1->unequip();
	weapon->wield();
	message_vision(HIC"\n$N趁机刀交左手，右手拔出" + weapon->name() + HIC"，并用内力控制音律，奏出一曲"+HIY"[大漠雁歌]"+HIC"！\n"NOR,me,target);
	message_vision(YEL"\n好一个：绝域苍茫，大漠穷秋。\n\n\t\t"+RED"大漠孤烟直，长河落日圆！\n"NOR,me,target);
	if( random(ap) > dp/3 )
	{
		target->start_busy(3+random(3));
		message_vision(YEL"\n$n眼前景物随着你的箫声飞快变化，$n渐渐沉迷其中，浑然忘我！\n"NOR,me,target);	
	}
	message_vision(HIC"\n$N箫声突变，婉转细腻，撩人心弦。正是当世名曲：「花前月下」！\n"NOR,me,target);
	if( target->is_busy() )
	{
		message_vision(HIC"\n$n眼前景物随之突变，$n一下乱了心神，周身经脉随着$N的箫声轻轻跃动！\n"NOR,me,target);
		message_vision(HIC"\n$N箫声再变，越来越细，越拔越高，仿佛慢慢步入云端，俯瞰人世！\n"NOR,me,target);
		message_vision(HIR"\n$n脸上一抹红润闪过，“哇”的吐出一口鲜血，已然被$N箫声伤了经脉！\n"NOR,me,target);
		damage=ap + random(ap) - random(dp/2);
		if( damage < ap/2 ) damage = ap/2;
		target->receive_damage("kee",damage,me);
		target->receive_wound("kee",damage/2,me);
		COMBAT_D->report_status(target);
	}
	else if( random(ap+dp) > dp/2 )
	{
		target->start_busy(2+random(2));
		message_vision(HIC"\n$n正以内力抵抗$N箫声中山川萧条之悲意，不防$N吹箫之技已经出神入化，转换之间浑然天成，无迹可寻！\n"NOR,me,target);
		message_vision(CYN"\n$n赶紧运转心法想要抵御，不想心急出错，叉了内息，一时动弹不得！\n"NOR,me,target);
	}
	else
	{
		message_vision(HIC"\n$n循着$N的箫声进退自如，神情间似是十分享受！\n"NOR,me,target);
	}
	message_vision(HIC"\n$N渐觉心头一片清明，有若皓月当空，鲜花怒放！\n"NOR,me,target);
	message_vision(HIC"\n$N合着箫声，合着胸中浩然之气刺出一剑！\n"NOR,me,target);
	me->set_temp("XFS_perform",1);
	COMBAT_D->do_attack(me,target, weapon);
	me->delete_temp("XFS_perform");
	weapon->unequip();
	weapon1->wield();
        me->receive_damage("sen", ap/5);
        //me->add("force", -me->query_skill("yange-blade", 1));
	//me->start_busy(1+random(2));
	me->add("force", -ap/5);
	me->start_busy(1);
	if( (target->query("eff_kee")<0 || !living(target)) && !random(5) )  
        {
		str=target->name()+"被"+me->name()+"用五庄观绝学"+HIY+"「大漠雁歌」"+HIM+"震断全身经脉，七窍流血而亡！";
		message("channel:rumor",HIM"【空穴来风】某人："+str+"\n"NOR,users());
	}
        return 1;
}


