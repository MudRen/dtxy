//Cracked by Roath
#include <ansi.h>
#include <combat.h>
inherit SSERVER;
int perform(object me, object target)
{
        string msg;
        int extra,i,lmt;
        object weapon;
        extra = me->query_skill("qixiu-jian",1);
        if ( extra < 50) return notify_fail("���[���޽�]���������죡\n");
        extra = me->query_skill("huntian-qigong",1);
        if ( extra < 50) return notify_fail("���[��������]���������죬�޷��������޽���������\n");
//      if( me->query_temp("zxzx") ) 
//        return notify_fail("�������˹�,���ܷ������ã�\n");
        if( !target ) target = offensive_target(me);
        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("�۶����߽���ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if(me->query("family/family_name")!="�ݿ�ɽ�޵׶�")
                return notify_fail("�㲻���ñ��ɵ����⹥��\n");
				if( (int)me->query("force") < 500 )      
                return notify_fail("�������������\n");
        weapon = me->query_temp("weapon");
        msg = YEL  "$N���Դ󷢣����е�"+ weapon->name()+  "��籩������$nϮ����" NOR;
        me->add("force",-200);
        message_vision(msg,me,target);
        me->add_temp("apply/attack",extra/5);
        me->add_temp("apply/damage",extra/8);
        lmt = random(5)+3;
        for(i=1;i<=lmt;i++)
        {
        COMBAT_D->do_attack(me,target, me->query_temp("weapon"),TYPE_REGULAR,msg);
        }
        me->add_temp("apply/attack",-extra/5);
        me->add_temp("apply/damage",-extra/8);
        me->start_busy(2);
        return 1;
}
