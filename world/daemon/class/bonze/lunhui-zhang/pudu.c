// writted by jie
// 2/2001

#include <ansi.h>
#include <combat.h>

inherit SSERVER;

int perform(object me, object target)
{       
        string str,msg="";
        int damage,wound,skill;
	int cd = 6;
        object weapon=me->query_temp("weapon");
        if( !target ) target = offensive_target(me);
        if( !target
        ||      !target->is_character()
        ||      target->is_corpse()
        ||      target==me)
                return notify_fail("你要对谁施展「慈光普渡」？\n");
	if ( time() - me->query_temp("lastchaodu") < cd )
		return notify_fail("你刚刚使过「慈光普渡」绝招，还是歇会儿吧。\n");

        if(!me->is_fighting())
                return notify_fail("「慈光普渡」只能在战斗中使用！\n");
        
        if(!wizardp(me) && me->query("family/family_name")!="南海普陀山")
                return notify_fail("不是佛门弟子不能用「慈光普渡」！\n");
        // 佛门杀气高？好象不符合现实，所以设定这杀气条件
        if( (int)me->query("bellicosity") > 300 )
        return notify_fail("你的杀气太重，无法施展佛门绝技。\n");
                
        if (me->query_skill_mapped("force")!="lotusforce")
                return notify_fail("「慈光普渡」必须以莲台心法为底子！\n");
                
        if((int)me->query("max_force") < 500 )
                return notify_fail("你的内力不够！\n");

        if((int)me->query("force") < 500 )
                return notify_fail("你的内力不足！\n");
        if((int)me->query("sen") < 300 )
                return notify_fail("你的精神不足，没法子施用外功！\n");
        if((int)me->query_skill("lotusforce", 1) < 80)
                return notify_fail("你的莲台心法修为还不够，使用这一招会有困难！\n");
        if((int)me->query_skill("jienan-zhi", 1) < 80)
                return notify_fail("你的劫难指修为还不够，使用这一招会有困难！\n");
	me->add("force", -100);
	me->set_temp("lastchaodu",time());
        message_vision(HIY"$N气沉丹田，犹如金刚浑身发金光，招转佛门正宗绝招「慈光普渡」，向$n连续发动进攻！\n"NOR,me,target);
        me->set("ciguangpudu", 6);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"));
        
        me->set("ciguangpudu", 7);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"));
        
        me->set("ciguangpudu", 8);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"));
        
        me->set("ciguangpudu", 9);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"));
        
        me->delete("ciguangpudu");
        //me->start_busy(2+random(1));
	message_vision(RED"\n$N"+NOR+RED+"招式一变，右手收杖于背后，左手立掌礼佛！\n"NOR,me,target);
	message_vision(HIB"\n\n\n            〓"+HIG+"劫难刀"+HIB+"〓\n\n\n"NOR,me,target);
	message_vision(RED"一道森寒的无形刀锋劈向$n！\n"NOR,me,target);
	skill = me->query_skill("unarmed");
	if( random(skill + target->query_skill("unarmed") / 2) > target->query_skill("unarmed", 1) / 2 )
	{
		skill = me->query_skill("unarmed");
        	damage = random(skill / 2) + skill * 2;
        	damage -= target->query_temp("apply/armor");
           	if(damage < skill) damage = skill;           
           	target->receive_wound("kee", 1 + random(damage/2), me);
            	target->receive_damage("kee", damage, me);
            	message_vision(HIR"但听一声裂帛大响，$n"+HIR+"身上留下一条深深的血槽！\n"NOR,me,target);
             	COMBAT_D->report_status(target);
        }
        else
        {
        	message_vision(HIG"只见$N"+HIG+"狼狈的从掌刀下躲了过来。\n"NOR,target);
        }
        message_vision(HIY "\n$N周身大放光明，佛口开合：孽障，劫难已过，还不皈依？！\n"NOR, me, target);
        if( random(me->query_skill("buddhism",1)) > random(target->query_skill("spells",1)/4) )
        {
                message_vision(HIR "\n$n被$N的佛法感化，跪倒在地已经忘记了自己还在战斗之中！\n\n" NOR, me,target);
                damage = me->query_skill("spells");
                damage = damage + random(damage/3);
                target->receive_damage("sen",damage,me);
                target->receive_wound("sen",damage,me);
                COMBAT_D->report_sen_status(target);
        }
        else
                message_vision(HIC "\n$n大叫到：我命由天，不由你！\n\n" NOR, me,target);
        message_vision(HIW"$N低吟“阿弥陀佛！”「慈光普渡」用功完毕，身上淡淡的金光慢慢隐去.\n"NOR,me,target);
        message_vision(msg,me,target);
        if ( (target->query("eff_kee")<0 || !living(target)) && !random(5) )  
        {
        	str=target->name()+HIM"被"+me->name()+"用"+NOR+HIC"「慈光普渡」"+NOR+HIM"渡化，心甘情愿下了黄泉，再渡轮回。";
    		message("channel:rumor",HIM"【空穴来风】某人："+str+"\n"NOR,users());
	}
        me->add("kee", -100);
        me->add("sen",-100);
        return 1;
}
