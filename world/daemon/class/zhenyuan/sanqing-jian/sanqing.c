// sanqing.c һ��������

#include <ansi.h>
#include <skill.h>
#include <weapon.h>
#include <combat.h>
inherit SSERVER;
 
int perform(object me, object target)
{
        object weapon, ob;
        string msg, string1;
        int count;
 	if( !target ) target = offensive_target(me);

        if( !me->is_fighting(target) )
                return notify_fail("��һ�������塹ֻ����ս����ʹ�á�\n");
 
        if (!objectp(weapon = me->query_temp("weapon"))
        || (string)weapon->query("skill_type") != "sword")
                return notify_fail("��һ�������塹��ʼʱ��������һ�ѽ���\n");
	if( time()-(int)me->query_temp("sqpfm_end") < 4 )
                return notify_fail("�����ö�Ͳ����ˣ�\n");
        //if (me->query_temp("jianmang"))
        //   return notify_fail("������ʩ�ý�â��û����������һ�������塹��\n");
        if(!wizardp(me) && me->query("family/family_name") != "��ׯ��")
                return notify_fail("[һ��������]����ׯ�۲���֮�ܣ�\n");
        if( (int)me->query("force") < 500 )
                return notify_fail("�������������\n");
	me->add("force", -100);
        if( (int)me->query_skill("sanqing-jian",1) < 50 )
                return notify_fail("������彣���������ң��޷�ʹ�á�һ�������塹��\n");
        me->set_temp("sqpfm_end", time());
	me->add_temp("apply/attack", (int)me->query_skill("sanqin-jiang",1)/4);
	me->add_temp("apply/damage", (int)me->query_skill("sanqin-jiang",1)/4);
        msg = HIY "\n$Nʹ�����彣���ľ�����һ�������塹�����е�"+ weapon->name()+  HIY"����㹥������������\n\n" NOR;
        message_vision(msg, me);
        msg = HIB "ֻ��$N����һ����"+ weapon->name()+ HIB"����$n����磡\n" NOR;
        message_vision(msg, me,target);
        me->set_temp("sq_perform", 7);
        COMBAT_D->do_attack(me,target, me->query_temp("weapon"),TYPE_REGULAR);
        msg =  HIW "$N���ʹ���ڶ���,"+ weapon->name()+ HIW"����$n���Ҽ磡\n" NOR;
        message_vision(msg, me,target);
        me->set_temp("sq_perform", 8);
       	COMBAT_D->do_attack(me,target, me->query_temp("weapon"),TYPE_REGULAR);
        msg = HIC "$N��Хһ���������ڽ�����$n����ǰ������������\n" NOR;
        message_vision(msg, me,target);
        me->set_temp("sq_perform", 9);
        COMBAT_D->do_attack(me,target, me->query_temp("weapon"),TYPE_REGULAR);
        me->add_temp("apply/attack", -(int)me->query_skill("sanqin-jiang",1)/4);
	me->add_temp("apply/damage", -(int)me->query_skill("sanqin-jiang",1)/4);
	me->delete_temp("sq_perform");
        //me->start_busy(1+random(2));
        return 1;
}

