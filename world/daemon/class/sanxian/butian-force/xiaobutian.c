// xiaobutian.c С����
// written by mind 2001/2
// /daemon/class/sanxian/butian-force/xiaobutian.c

#include <ansi.h>

int exert(object me, object target, int amount)
{
        if( (string)me->query("family/family_name")!="����ɢ��")
                return notify_fail("���ɢ�ɣ�������תС�����ķ���\n");
        if( target != me ) return 
                notify_fail("��ֻ�ܶ��Լ���תС�����ķ���\n");

        if( me->is_fighting() )
                return notify_fail("ս���в�����תС�����ķ���\n");

        if( (int)me->query("force") < 400 )
                return notify_fail("�������������\n");

        if( (int)me->query("eff_kee") < (int)me->query("max_kee") / 4 )
                return notify_fail("���Ѿ����˹��أ�ֻ��һ��������������Σ�գ�\n");
        if( (int)me->query("eff_sen") < (int)me->query("max_sen") / 4 )
                return notify_fail("���Ѿ����˹��أ�ֻ��һ��������������Σ�գ�\n");

        write( HIW "������ǱԪ��һ��ָ�죬һ�ֵ�أ���ʼ��תС�����ķ���\n" NOR);
        message("vision",
                HIW + me->name() + "һ��ָ�죬һ�ֵ�أ���ȡ������¾��������ã���ɷ�������ӡ�\n" NOR,
                environment(me), me);

        me->receive_curing("kee", (int)me->query("max_kee"));
        me->receive_curing("sen", (int)me->query("max_sen"));
        me->set("kee", (int)me->query("max_kee"));
        me->set("sen", (int)me->query("max_sen"));
        me->add("force", -400);
        me->set("force_factor", 0);
        me->start_busy(2);

        return 1;
}

