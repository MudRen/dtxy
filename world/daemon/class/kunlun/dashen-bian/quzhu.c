//class
// youling xian shen sanxian fighter yaomo bonze swordsman,dragon
// youling ���
// dragon  ����
// human   ����
// xian    xian,shen,sanxian,bonze ����
// yaomo   ��ħ
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
                return notify_fail("������ħֻ�ܶ�ս���еĶ���ʹ�á�\n");
        if(me->query("family/family_name")!="����ɽ���鶴")
        	return notify_fail("��������ħ��ֻ������ɽ���鶴���˲ſ����ã�\n");
        if ( !me->query("quzhu_known") )
        	return notify_fail("�㻹û��ѧ�ᡰ������ħ����\n");
        if ( me->query("force") < 1500 )
        	return notify_fail("�������������\n");
        if (me->query_skill("dashen-bian",1) < 200)
        	return notify_fail("��Ĵ���޷����д���ߡ�\n");
        if (me->query_skill("xuanzong-force",1) < 200)
        	return notify_fail("��������ķ����д���ߡ�\n");
        if (me->query_skill("yuxu-spells",1) < 200)
        	return notify_fail("��������ɷ����д���ߡ�\n");
        if (me->query_skill("kaitian-zhang",1) < 200)
        	return notify_fail("��Ŀ����Ʒ����д���ߡ�\n");
        if (me->query_skill("wugou-jian",1) < 200)
        	return notify_fail("����⹳�������д���ߡ�\n");
        if (me->query_skill("huntian-jian",1) < 200)
        	return notify_fail("��Ļ���һ�����д���ߡ�\n");
        
	if( me->query("lunhui_zhuanshi") > 1 )
		cd -= me->query("lunhui_zhuanshi") - 1;
        if ( time() - me->query_temp("quzhu_end") < cd )
        	return notify_fail("������ħ����Ƶ��ʹ�á�\n");
        me->set_temp("quzhu_end",time());
        me->add("force",-600);
	weapon = me->query_temp("weapon");
	tweapon = target->query_temp("weapon");
	tcls = target->query("class");
	myexp=me->query("combat_exp")/10000;
	yourexp=target->query("combat_exp")/10000;
	enhance=me->query_skill("xuanzong-force",1);
    	damage=me->query_skill("yuxu-spells",1);
	msg = HIR"\n$Nʹ�˸�������������"+weapon->name()+HIR"������գ�"+weapon->name()+HIR"����������⣬��$nȫ����ס��\n" NOR;
	msg = msg + RED"$N�ټ���һ��"+HIW+"����"+NOR+RED"������֮�У���ϸ̽��$n�ĵ�ϸ��\n"NOR;
	msg = msg + WHT"\n$N΢΢һЦ���������г���$N���һ����"+HBBLU+"����"NOR+WHT"��"+BLINK;
	if( random(myexp) < yourexp/(2+me->query("quzhu_known")) )
	{
		me->set_temp("quzhu_end",time()-5);
		if( tcls == "youling" )
			msg = msg + HIG"����"NOR+WHT+"������"NOR;
		else if( tcls == "dragon" )
			msg = msg + HIB"���"NOR+WHT+"������"NOR;
		else if( tcls == "yaomo" )
			msg = msg + HIY"����"NOR+WHT+"������"NOR;
		else if( tcls == "fighter" || tcls == "swordsman" )
			msg = msg + HIC"����"NOR+WHT+"������"NOR;
		else if( tcls == "xian" || tcls == "shen" || tcls == "sanxian" || tcls == "bonze" )
			msg = msg + HIR"��ħ"NOR+WHT+"������"NOR;
		else
			msg = msg + HIM"������"NOR+WHT+"������"NOR;
		msg = msg + HIR"\n\n$n������Ц�����ϵ��ˣ����������߳��˺�⡣\n"NOR;
		message_vision(msg, me, target);
		return 1;
	}
	/*else if( tweapon )
	{
		me->start_busy(2);
		me->set_temp("quzhu_end",time()-5);
		target->start_busy(1 + random(me->query("quzhu_known")));
		msg = msg + BLK"�⹳"NOR+WHT+"������"NOR;
		msg = msg + HIR"\n\n��⻯��һ���⹳������������$n��"+tweapon->name()+HIR"�ϡ�\n" NOR;
		if( random(me->query_skill("wugou-jian",1)) > target->query_skill("parry",1)/3 )
		{
			msg = msg + HIW"\n$N��ʹ�����������⹳��������һ����"+tweapon->name()+HIW"��ʱ���ַɳ���\n"NOR;
			message_vision(msg, me, target);
			tweapon->unequip();
			tweapon->move(environment(me));
		}
		else
		{
			msg = msg + HIW"\n$n���Ӧ�䣬��΢������"+tweapon->name()+HIW"˳��һ��һ����˻�����\n"NOR;
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
			msg = msg + HIB"���"NOR+WHT+"������"NOR;
		else if( tcls == "dragon" )
			msg = msg + HIC"����"NOR+WHT+"������"NOR;
		else if( tcls == "yaomo" )
			msg = msg + HIR"��ħ"NOR+WHT+"������"NOR;
		else if( tcls == "fighter" || tcls == "swordsman" )
			msg = msg + HIG"����"NOR+WHT+"������"NOR;
		else if( tcls == "xian" || tcls == "shen" || tcls == "sanxian" || tcls == "bonze" )
			msg = msg + HIY"����"NOR+WHT+"������"NOR;
		else
			msg = msg + HIM"̫������"NOR+WHT+"������"NOR;
		msg = msg + HIR"\n\n��⻯��һ��˿������$n��ͷ���Ź��˸����ʵʵ��\n" NOR;
		msg = msg + HIW"\n$N�ۼ�$n����ס���ִ�һ����"+HBBLU+"����"NOR+HIW"��"+BLINK"����"+NOR+HIW"������\n"NOR;
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
