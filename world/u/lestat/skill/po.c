//lestat for ����ɽ
//2001 ������
 
#include <ansi.h>

inherit F_DBASE;
inherit SSERVER;

int perform(object me, object target)
{
        object weapon;
        int skill;

       string msg;

        if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      target->is_corpse()
        ||      target==me)
                return notify_fail("��Ҫ��˭ʩչ�������ơ�?\n");
        if(me->query_temp("BAIGU_perform")) 
                return notify_fail("���Ѿ�ʹ���������ơ��ˣ�\n");
        if( time()-(int)me->query_temp("BAIGU_end") < 3 )
                return notify_fail("�����ö�Ͳ����ˣ�\n");

        if(!me->is_fighting(target) )
                return notify_fail("������ֻ����ս����ʹ��!!\n");

        if((int)me->query("max_force") <1000 )
                return notify_fail("�������������\n");

        if((int)me->query("force") < 500 )
                return notify_fail("����������㣡\n");

        if((int)me->query("sen") <50 )
                return notify_fail("��ľ����㣬û����ʩ���⹦��\n");
/*
        if((int)me->query_skill("jueqingbian",1) <100)
                return notify_fail("��ľ���޼��𻹲���ʩչ��һ��������!!\n");
        if((int)me->query_skill("moondance",1) <100)
                return notify_fail("�������������ȼ�����!!\n");
        if((int)me->query_skill("moonforce",1)<100)
                return notify_fail("���Բ���ķ��ȼ�̫��!!\n");
        if((int)me->query_skill("moonshentong",1) <100)
                return notify_fail("����¹��ɷ��ȼ�����!!\n");
        if(me->query("family/family_name") != "�¹�" )
                return notify_fail("���������Ե,���򲻵��޷��ľ���!!\n");
*/
        me->delete("env/brief_message");
        target->delete("env/brief_message");

//        ap = 2 + random(1);
        weapon=me->query_temp("weapon");
     msg = HIC
"\n$NĬ�������ķ���ͻȻ˫�Ʊ�צ��ʹ�������ƾ�ѧ"HIR"�������ơ�"HIC"���������࣬����һƬצӰ�Ӱ���б���$n!\n" NOR;
    message_vision(msg, me, target);


        skill = me->query_skill("unarmed");
        me->set_temp("BAIGU_perform", 1);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"));

        me->start_call_out( (: call_other, __FILE__, "remove_effect", me :), skill/10);
        me->add("force", -200);
        return 1;
}

void remove_effect(object me, int amount)
{       
	if ( me->query_temp("BAIGU_perform") ) {
        message_vision(HIM"$N��ͷ��ð������ĺ��飬�����𽥱仺��\n"NOR, me);
        me->delete_temp("BAIGU_perform");
        me->set_temp("BAIGU_end",time());
         }
}
