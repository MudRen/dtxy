// shengsi������   ziwuliuzhu������ע
// /daemon/class/sanxian/mysticism/shengsi.c
// writted by mind 2001/2

#include <ansi.h>
inherit SSERVER;
int cast(object me, object target)
{
        if (me->query("family/family_name")!="����ɢ��")
                return notify_fail("�㲻������ɢ�ɣ����ᡸ����������\n");
        if (!target)target=offensive_target(me);
        if (!target||!target->is_character() || !me->is_fighting(target))
                return notify_fail("����������ֻ�ܶ�ս���еĶ���ʹ�á�\n");
        if ((int)me->query_skill("mysticism",1) <80)
                return notify_fail("��[�������]���򻹲����ң����ᡸ����������\n");
        //if(target->query_temp("mark/ziwuliuzhu") == 1)
        //return notify_fail(target->query("name")+"�Ѿ�����������ע��\n");  
        if ((int)me->query("mana")<200)
                return notify_fail("��ķ���������\n"); 
        if((int)me->query("sen") < 100 )
                return notify_fail("���޷����о�����\n");
        if (me->query("betrayer") || me->query("betray/count"))
           return notify_fail("���Ķ����ߺ�������ɢ�ɵľ������ڡ�\n");
        
        me->add("mana", -200);
        me->receive_damage("sen", 100);
        message_vision(HIW"$N��ָһ�㣬����$n��̾һ���������������ӣ���\n" NOR,me,target);
        
                     
        if (random(me->query("daoxing"))>(int)target->query("daoxing")/3*2 ) {                                   
                target->start_busy(1);                    
                me->start_busy(1+random(2));  
                message_vision(HIC"$n��$Nһ��������Ԫ���й��\n"NOR,me,target);             
                target->apply_condition("ziwuliuzhu_poison",(int)me->query_skill("mysticism",1)/10+1);
                target->set_temp("mark/ziwuliuzhu", 1);
                tell_object(target,HIB"�͵�����о�ʲô����Ķ�������Ԫһת���ƺ�����ʲô�����ƺ�����ʲô��\n"NOR); 
                if( living(target) ) target->kill_ob(me);
        } else {        
                message_vision(HIC"����$n��Ԫ�ع̣���ס���񣬵�Ҳ���ų�һ���亹��\n"NOR,me,target);
                me->start_busy(3);
        }
        return 1;
}


