//class
// youling xian shen sanxian fighter yaomo bonze swordsman,dragon
// youling 夺魂
// dragon  擒龙
// human   定身
// xian    xian,shen,sanxian,bonze 缚神
// yaomo   困魔
#include <ansi.h>
#include <combat.h>
inherit SSERVER;
int perform(object me, object target)
{
	string msg,tcls;
	int myexp,yourexp,enhance,damage;
	object weapon,tweapon;
	int i = 0;
	int cd = 10;
        if( !target ) target = offensive_target(me);
        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("驱神逐魔只能对战斗中的对手使用。\n");
        if(me->query("family/family_name")!="昆仑山玉虚洞")
        	return notify_fail("“驱神逐魔”只有昆仑山玉虚洞门人才可以用！\n");
        if ( !me->query("quzhu_known") )
        	return notify_fail("你还没有学会“驱神逐魔”。\n");
        if ( me->query("force") < 1500 )
        	return notify_fail("你的内力不够。\n");
        if (me->query_skill("dashen-bian",1) < 200)
        	return notify_fail("你的打神鞭法还有待提高。\n");
        if (me->query_skill("xuanzong-force",1) < 200)
        	return notify_fail("你的玄宗心法还有待提高。\n");
        if (me->query_skill("yuxu-spells",1) < 200)
        	return notify_fail("你的玉虚仙法还有待提高。\n");
        if (me->query_skill("kaitian-zhang",1) < 200)
        	return notify_fail("你的开天掌法还有待提高。\n");
        if (me->query_skill("wugou-jian",1) < 200)
        	return notify_fail("你的吴钩剑法还有待提高。\n");
        if (me->query_skill("huntian-jian",1) < 200)
        	return notify_fail("你的混天一剑还有待提高。\n");
        
	if( me->query("lunhui_zhuanshi") > 1 )
		cd -= me->query("lunhui_zhuanshi") - 1;
        if ( time() - me->query_temp("quzhu_end") < cd )
        	return notify_fail("驱神逐魔不能频繁使用。\n");
        me->set_temp("quzhu_end",time());
        me->add("force",-600);
	weapon = me->query_temp("weapon");
	tweapon = target->query_temp("weapon");
	tcls = target->query("class");
	myexp=me->query("combat_exp")/10000;
	yourexp=target->query("combat_exp")/10000;
	enhance=me->query_skill("xuanzong-force",1);
    	damage=me->query_skill("yuxu-spells",1);
	msg = HIR"\n$N使了个法诀，将手中"+weapon->name()+HIR"祭到半空，"+weapon->name()+HIR"放射出万道红光，将$n全身罩住！\n" NOR;
	msg = msg + RED"$N再祭出一朵"+HIW+"白莲"+NOR+RED"射入红光之中，仔细探察$n的底细。\n"NOR;
	msg = msg + WHT"\n$N微微一笑，似是胸有成竹。$N大喝一声："+HBBLU+"混沌"NOR+WHT"●"+BLINK;
	if( random(myexp) < yourexp/(2+me->query("quzhu_known")) )
	{
		me->set_temp("quzhu_end",time()-5);
		if( tcls == "youling" )
			msg = msg + HIG"定身"NOR+WHT+"～～～"NOR;
		else if( tcls == "dragon" )
			msg = msg + HIB"夺魂"NOR+WHT+"～～～"NOR;
		else if( tcls == "yaomo" )
			msg = msg + HIY"缚神"NOR+WHT+"～～～"NOR;
		else if( tcls == "fighter" || tcls == "swordsman" )
			msg = msg + HIC"擒龙"NOR+WHT+"～～～"NOR;
		else if( tcls == "xian" || tcls == "shen" || tcls == "sanxian" || tcls == "bonze" )
			msg = msg + HIR"困魔"NOR+WHT+"～～～"NOR;
		else
			msg = msg + HIM"忘词了"NOR+WHT+"～～～"NOR;
		msg = msg + HIR"\n\n$n哈哈大笑：你上当了！接着慢步走出了红光。\n"NOR;
		message_vision(msg, me, target);
		return 1;
	}
	/*else if( tweapon )
	{
		me->start_busy(2);
		me->set_temp("quzhu_end",time()-5);
		target->start_busy(1 + random(me->query("quzhu_known")));
		msg = msg + BLK"吴钩"NOR+WHT+"～～～"NOR;
		msg = msg + HIR"\n\n红光化作一把吴钩剑，正好锁在$n的"+tweapon->name()+HIR"上。\n" NOR;
		if( random(me->query_skill("wugou-jian",1)) > target->query_skill("parry",1)/3 )
		{
			msg = msg + HIW"\n$N再使个法诀，将吴钩剑往横里一拉，"+tweapon->name()+HIW"登时脱手飞出！\n"NOR;
			message_vision(msg, me, target);
			tweapon->unequip();
			tweapon->move(environment(me));
		}
		else
		{
			msg = msg + HIW"\n$n随机应变，略微用力将"+tweapon->name()+HIW"顺势一送一搭，抽了回来！\n"NOR;
			message_vision(msg, me, target);
		}
		return 1;
	}*/
	else
	{
		me->start_busy(2);
		target->start_busy(me->query("quzhu_known") + random(1+me->query("quzhu_known")));
		/*if( me->query_temp("pfmxue") )
		{
			me->delete_temp("pfmxue");
			me->set_temp("havexue",1);
		}*/
		if( tcls == "youling" )
			msg = msg + HIB"夺魂"NOR+WHT+"～～～"NOR;
		else if( tcls == "dragon" )
			msg = msg + HIC"擒龙"NOR+WHT+"～～～"NOR;
		else if( tcls == "yaomo" )
			msg = msg + HIR"困魔"NOR+WHT+"～～～"NOR;
		else if( tcls == "fighter" || tcls == "swordsman" )
			msg = msg + HIG"定身"NOR+WHT+"～～～"NOR;
		else if( tcls == "xian" || tcls == "shen" || tcls == "sanxian" || tcls == "bonze" )
			msg = msg + HIY"缚神"NOR+WHT+"～～～"NOR;
		else
			msg = msg + HIM"太极无形"NOR+WHT+"～～～"NOR;
		msg = msg + HIR"\n\n红光化作一条丝带，将$n从头到脚裹了个结结实实。\n" NOR;
		msg = msg + HIW"\n$N眼见$n被制住，又大喊一声："+HBBLU+"混沌"NOR+HIW"●"+BLINK"开天"+NOR+HIW"～～～\n"NOR;
		message_vision(msg, me, target);
		target->add_temp("apply/dodge",-enhance/2);
        	target->add_temp("apply/parry",-damage/2);
        	me->add_temp("apply/attack",enhance/2);
    		me->add_temp("apply/damage",damage/2);
    		for( i=1;i <= me->query("quzhu_known");i++ )
    			COMBAT_D->do_attack(me, target, weapon);
	    	seteuid(getuid());
	    	weapon->set_temp("original/use_apply_skill",weapon->query("use_apply_skill"));
	    	weapon->set_temp("original/skill_type",weapon->query("apply/skill_type"));
		me->set("actions", (: call_other, SKILL_D("kaitian-zhang"), "query_action" :) );
	    	weapon->set("use_apply_skill",1);
	    	weapon->set("apply/skill_type","unarmed");
	    	COMBAT_D->do_attack(me, target);
	    	seteuid(getuid());
	    	me->set("actions", (: call_other, SKILL_D("wugou-jian"), "query_action" :) );
	    	weapon->set("apply/skill_type","sword");
	    	COMBAT_D->do_attack(me, target,weapon);
	    	seteuid(getuid());
	    	me->set("actions", (: call_other, SKILL_D("huntian-jian"), "query_action" :) );
	    	//weapon->set("apply/skill_type","sword");
	    	COMBAT_D->do_attack(me, target,weapon);
	    	weapon->set("use_apply_skill",weapon->query_temp("original/use_apply_skill"));
    		weapon->set("apply/skill_type",weapon->query_temp("original/skill_type"));
    		me->reset_action();
    		/*if( me->query_temp("havexue") )
		{
			me->set_temp("pfmxue",1);
			me->delete_temp("havexue");
		}*/
		target->add_temp("apply/dodge",enhance/2);
	        target->add_temp("apply/parry",damage/2);
	        me->add_temp("apply/attack",-enhance/2);
	    	me->add_temp("apply/damage",-damage/2);
		return 1;
	}
	return 1;
}
