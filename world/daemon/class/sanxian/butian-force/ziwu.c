// ziwu.c
// written by mind 2001/2
// /daemon/class/sanxian/butian-force/ziwu.c

#include <ansi.h>

int exert(object me, object target)
{

        if ( !target
      ||      !userp(target)
      ||      target->is_corpse()
      ||      target==me)
                return notify_fail("������˭��������ע��\n");
        if (!target->query_condition("ziwuliuzhu_poison"))
        return notify_fail("û��������עϹ����ʲô��\n");
        if( me->is_fighting() || target->is_fighting())
                return notify_fail("ս�����޷��˹����ˣ�\n");

        if( (int)me->query("force") - (int)me->query("max_force") <  400 )
                return notify_fail("�������������\n");

    if ((int)me->query_skill("butian-force",1)<80)
                return notify_fail("����ڹ���Ϊ���������˰�������ע��\n");
        
      if (me->query("betrayer") || me->query("betray/count"))
           return notify_fail("���Ķ����ߺ�������ɢ�ɵľ������ڡ�\n");
      
      
        message_vision(
                HIM "$N��������ѭ��$n���ڣ���Ѱ���޼����ٵ�������ע��\n\n"NOR,me, target );
    if (random(me->query_skill("butian-force", 1)-40)>10){
                target->apply_condition("ziwuliuzhu_poison",0);
                message_vision(
                HIY "$n�о�һ��ů�������ڻ�����ת������ס������������˯�硣\n"NOR,me, target );
                target->command_function("sleep");
                }
        else {
                message_vision(
                HIR "$N���񲻼ã���������Ҫ��ɢ����Ż��һ��Ѫ������\n"NOR,me, target );
        }       
 
        target->receive_cuiring("kee", 10 + (int)me->query_skill("force")/3 );
        me->add("force", -150);
        me->set("force_factor", 0);
        return 1;
}

