//Cracked by Roath

//Ansi 99.12
#include <ansi.h>

inherit SSERVER;

int perform(object me, object target)
{
        int ap,dp,damage,chance;
        string msg;
        object weapon;
                
        if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      target->is_corpse()
        ||      target==me)
                return notify_fail("��Ҫ��˭ʩչ����ˮ�޺ۡ���\n");

        if(!me->is_fighting(target))
                return notify_fail("����ˮ�޺ۡ�ֻ����ս����ʹ�ã�\n");
        if(me->query("family/family_name")!="��ɽ��")
                return notify_fail("������ɽ�Ĳ����á���ˮ�޺ۡ���\n");
//        if(me->query("shushan/duanshui_master")!=1)
//                return notify_fail("�㻹û��ᡸ��ˮ�޺ۡ���\n");

        if((int)me->query("max_force") < 500 )
                return notify_fail("�������������\n");

   	if((int)me->query("force") < 500 )
     		return notify_fail("����������㣡\n");

        if((int)me->query("sen") < 300 )
                return notify_fail("��ľ����㣬û����ʩ���⹦��\n");

        if((int)me->query_skill("yujianshu", 1) < 50)
                return notify_fail("��Ľ�����Ϊ��������ʹ����һ�л������ѣ�\n");
	if( time()-(int)me->query_temp("duanshui_end") < 4 )
                return notify_fail("�����ö��ˣ��Ͳ����ˣ�\n");
        me->set_temp("duanshui_end",time());

        msg = CYN"\n$N����ζ��缲�磬�Կ�����ǧ�߷������ٶȣ�ֱ��$n��\n"NOR;
        ap = me->query_skill("sword");
        ap = me->query("combat_exp");
        dp = target->query("combat_exp")/4*5; 
	if ( dp <= 0 ) dp = 1;
        chance = (int)(random( ap + dp ) / dp * 100);
        if (target->is_busy()) chance *= 2;
        if( chance > 40 ) {
                damage = me->query_skill("sword") * 2 + me->query("force_factor");
                if (damage > 800) damage = 750+random(75);
                target->receive_damage("kee",damage,me);
                target->receive_wound("kee",damage/3,me);
		//target->start_busy(random(1)+1);
                msg += CYN"���$n��$N�ġ���ˮ�޺ۡ�����������\n"NOR;
        }
        
        else 
                msg += "���Ǳ�$n�㿪�ˡ�\n"NOR;
        message_vision(msg, me, target);
        if( damage > 0 ) COMBAT_D->report_status(target);
        me->add("force",-damage/2);
        me->start_busy(1);
        return 1;
}
