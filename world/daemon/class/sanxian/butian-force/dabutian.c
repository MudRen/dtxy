// dabutian.c ����
// written by mind 2001/2
// /daemon/class/sanxian/butian-force/dabutian.c

#include <ansi.h>

int exert(object me, object target, int amount)
{       
        int skill,force;  
        skill = (int)me->query_skill("butian-force",1);  
        if(skill < 50) return notify_fail("��Ĳ����ķ�̫���ˣ�������ת�����ķ���\n"); 
        if( !target || target == me)  return notify_fail("��Ҫ��˭ʹ�ô����ķ���\n" );
        if( me->is_fighting() || target->is_fighting())
                return notify_fail("ս�����޷�ʹ�ô����ķ���\n");
        if((int)me->query("max_force") < 400)
                return notify_fail("�����������ǿ��\n");
        if((int)me->query("max_force") <= (int)target->query("max_force"))      
                return notify_fail("���������û��"+target->name()+"��ǿ������Ϊ����ת�����ķ���\n"); 
        message_vision(
                HIR "$N��������ķ���ȫ��������ʣ���ָ����$n�����Ѩ....\n\n"
                "���˲��ã�$n������һ�����ɰ���������������ʶ�Ŀ��$Nȴ�赹�ڵء�\n" NOR,
                me, target );
        me->set_skill("butian-force",skill-2);
        me->add("max_force",-400);
        me->set("force",0);
        target->add("max_force",200);
        me->unconcious();
        return 1;
}

