#include <ansi.h>

inherit SSERVER;

int cast(object me, object target)
{
        string msg,start;
        int ap, dp, success;
        target = offensive_target(me);
        //always use the one who is fighting me as target.

        if( me->is_busy())
                return notify_fail("����æ���أ���Ӧ����ǰ���°ɡ�\n");

        if( (int)me->query("mana") < 100 )
                return notify_fail("��ķ��������ˣ�\n");

        if( (int)me->query("sen") < (int)me->query("max_sen")/5 )
                return notify_fail("�㾫��̫����Լ��о������䡣\n");

        if( (int)me->query_skill("yuxu-spells", 1) < 20)
                return notify_fail("��δ��ѧ���ݡ�\n");

        if(environment(me)->query("under_water"))
                return notify_fail("����ˮ�У�û��ʩ�û�ݣ�\n");

        ap=me->query_skill("spells")+me->query("max_mana")/10;
        if(target) dp=target->query_skill("spells")+target->query("max_mana")/10;

        if(!me->is_fighting() )
        {
                message_vision(HIR"$N������׳�һƬ��ɳ������䣬������в����ˡ�\n"NOR,me);
                me->add("sen", -me->query("max_sen")/8);
                me->add("mana", -80);
                success=1;
        }
        else
        {
                msg=HIR"��ս�У�$NͻȻ����սȦ���������һ�ѻ�ɳ�������˼����䡣\n"NOR;
                if(random(ap+dp)>dp/2)
                {
                        msg+=HIR"ֻ��$N����һ�����ߣ�������Ӱ�Ѿ������ˡ�\n"NOR;
                        me->add("sen", -me->query("max_sen")/6);
                        me->add("mana", -50);
                        success=1;
                }
                else msg+=HIR"��$n����Ӱ�ѽ������ϣ���$N����������\n"NOR;
                me->add("mana", -50);
                message_vision(msg, me, target);
        }
        if(success)
        {
                start="/d/kunlun/wuchang";
                me->move(start);
                message("vision", "ͻȻһ�Ż�������" +HIR+me->name()+"�������˳�����\n"NOR,
                                  environment(me), me);
                tell_object(me, HIR"�����ӰͻȻ������һ���һ��С�\n"NOR);
                return 3+random(3);
        }
        return 5+random(5);
        //if failed, can't use for a while.
}
