/*
	『愁思烈杀式』：重来云山，愁情盈袖，满目皆秋。
从来愁字折尽人，这一式以愁思意境激起人内心中的潜能，化作至烈绝杀。 

	『离别亢怒式』：别方不定，别理千名，有别必怨，有怨必盈。
离别亢怒式将离别时盈满的怨气转成杀机，再将杀气一剑泄出，取人性命。 

	『断肠绝灭式』：娇嗔浅笑俱因痴，断肠旧事知为谁？
两地相隔的愁思，生死永诀的别离，终于化作了这断肠绝灭的一剑。 
甚么山盟海誓，甚么地老天荒，终是抵不住一次阴阳相隔的午夜梦回。 
剑在人亦在，剑碎人断肠！ 

*/
#include <ansi.h>
#include <combat.h>
inherit SSERVER;
int perform(object me, object target)
{
        string msg;
        int extra,damage,ap,dp;
        object weapon;
        int cd = 10;
       	if( !wizardp(me) && (string)me->query("family/family_name") != "阎罗地府" )
                return notify_fail("[惊天三式]是冥界不传之密！\n");
        if( !me->query("jingtian_known") )
                return notify_fail("你还没有学会[惊天三式]！\n");
        extra = me->query_skill("zhuihun-sword",1);
	if( me->query("force") < 1800 ) 
		return notify_fail("你的状态不好，无法使出[图穷匕现]。\n");
        if ( extra < 200) 
        	return notify_fail("你的追魂剑法级别还不够，使用这一招还有一定难度！\n");
        if( (int)me->query_skill("sword", 1) < 200)
                return notify_fail("你的剑法还欠缺熟练，无法得心应手。\n");
        if( (int)me->query_skill("tonsillit", 1) < 200)
                return notify_fail("你的摄气诀等级太低。\n");
        if( !target ) target = offensive_target(me);
        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("［惊天三式］只能在战斗中使用。\n");
        
	if( me->query("lunhui_zhuanshi") > 1 )
		cd -= me->query("lunhui_zhuanshi") - 1;
       	if( time()-me->query_temp("jingtian_end") < cd ) 
       		return notify_fail("惊天三式不能用得这么频繁！\n");         
        me->set_temp("jingtian_end",time());
        weapon = me->query_temp("weapon");
        ap = me->query_skill("tonsillit",1);
        dp = target->query_skill("dodge",1);
        msg = HIB"\n$N怒哼一声：天地不仁，以万物为刍狗！胸中怨怒之气喷薄而发！\n" NOR;
        message_vision(msg,me,target);
        msg = YEL"\n『"HIB"愁思"HIR"烈杀"HIC"式"NOR+YEL"』－－\n" NOR;
        msg += CYN"\n重来云山，愁情盈袖，满目皆秋。\n" NOR;
        msg += CYN"从来愁字折尽人，这一式以愁思意境激起人内心中的潜能，化作至烈绝杀。\n" NOR;
        message_vision(msg,me,target);
        damage = extra*2 + me->query_skill("force") + me->query_str();
	damage = damage - target->query_temp("apply/armor");
	if( damage < me->query_skill("sword") ) damage = me->query_skill("sword");
        if( random(ap+dp) > dp/2 )
        {
        	damage = damage + random(damage/4);
        	msg = RED"\n$n被$N无尽愁思感染，心中怨天尤人，浑然忘记了躲避$N的至烈绝杀！\n" NOR;
        	target->receive_damage("kee",damage,me);
	        target->receive_wound("kee",damage/2,me);
	        me->add("force",-damage/5);
	        message_vision(msg, me, target);
	        COMBAT_D->report_status(target);
        }
        else
        {
        	me->add("force",-100);
        	COMBAT_D->do_attack(me, target, weapon);
        }
        if( me->query("jingtian_known") > 1 )
        {
        	msg = YEL"\n『"HIB"离别"HIR"亢怒"HIC"式"NOR+YEL"』－－\n" NOR;
        	msg += WHT"\n别方不定，别理千名，有别必怨，有怨必盈。\n" NOR;
        	msg += WHT"离别亢怒式将离别时盈满的怨气转成杀机，再将杀气一剑泄出，取人性命。\n" NOR;
        	message_vision(msg,me,target);
        	if( random(ap+dp) > dp/2 )
	        {
	        	damage = damage + random(damage/3);
	        	msg = RED"\n$n被$N盈满的怨气感染，胸中尽是离情别绪，结果被$N一剑穿心！\n" NOR;
	        	target->receive_damage("kee",damage,me);
		        target->receive_wound("kee",damage/2,me);
		        me->add("force",-damage/5);
		        message_vision(msg, me, target);
		        COMBAT_D->report_status(target);
	        }
	        else
	        {
	        	me->add("force",-100);
	        	COMBAT_D->do_attack(me, target, weapon);
	        }
        }
        if( me->query("jingtian_known") > 2 )
        {
        	msg = YEL"\n『"HIB"断肠"HIR"绝灭"HIC"式"NOR+YEL"』－－\n" NOR;
        	msg += HIM"\n娇嗔浅笑俱因痴，断肠旧事知为谁？\n" NOR;
        	msg += HIM"两地相隔的愁思，生死永诀的别离，终于化作了这断肠绝灭的一剑。\n" NOR;
        	msg += HIM"甚么山盟海誓，甚么地老天荒，终是抵不住一次阴阳相隔的午夜梦回。\n" NOR;
        	msg += HIY"\n\t\t剑在人亦在，剑碎人断肠！\n" NOR;
        	message_vision(msg,me,target);
        	if( random(ap+dp) > dp/2 )
	        {
	        	damage = damage + random(damage/2);
	        	msg = RED"\n$n被$N的痴心断肠感染，心如死灰，了无生趣，径直向$N的剑尖撞来！\n" NOR;
	        	target->receive_damage("kee",damage,me);
		        target->receive_wound("kee",damage/2,me);
		        me->add("force",-damage/5);
		        message_vision(msg, me, target);
		        COMBAT_D->report_status(target);
	        }
	        else
	        {
	        	me->add("force",-100);
	        	COMBAT_D->do_attack(me, target, weapon);
	        }
        }
        me->start_busy(2);
        return 1;
 }
