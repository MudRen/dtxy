#include <ansi.h>
inherit SSERVER;
int perform(object me, object target)
{
        object weapon;
int i,j,k,u,damage;
weapon = me->query_temp("weapon");
        if( !target ) target = offensive_target(me);
        if( !target
        ||      !target->is_character()
        ||      target->is_corpse()
        ||      target==me)
                return notify_fail("��Ҫ����˭��\n");
        if(me->query("family/family_name")!="��ɽ����")
                return notify_fail("�㲻����ɽ���ӣ�����ʹ������ܣ�\n");
        if(!me->is_fighting())
                return notify_fail("����û���ڴ�ܣ�\n");
        if((int)me->query("max_force") < 1000 )
                return notify_fail("����ڹ�̫�\n");
        if((int)me->query("force") < 500 )
                return notify_fail("����������㣡\n");
        if((int)me->query("sen") < 200 )
                return notify_fail("��ľ����㣬û����ʩ���⹦��\n");
	if((int)me->query_skill("xianfeng-spells", 1) < 100)
        	return notify_fail("����ɷ��������ȼ�����������ʹ����һ�У�\n");
	k=(int)me->query_skill("sword");
       j=(int)target->query_skill("dodge");
                  if(k<150)        
                return notify_fail("��Ľ������𻹲�����ʹ����һ�л������ѣ�\n");
u=1+k/50;
if (u>5) u=5;
me->delete("env/brief_message");
	target->delete("env/brief_message");
message_vision(HIB"\n$N��������һ����"NOR,me,target);
message_vision(HIW"\n���ҿ˵����ʹƽ�һ����"NOR,me,target);
message_vision(HIB"\nһɲ�Ǽ�ǧ�򽣹��ƿն�������������$n"NOR,me,target);
for (i=0;i<=u;i++)
{
if (random(k+j)>j) {
           message_vision(HIY"\n$nһ������������һ��"NOR,me,target);
damage=100+random(100);
target->receive_damage("kee",damage);
target->receive_wound("kee",damage/3);
	    COMBAT_D->report_status(target);
me->receive_damage("sen", 10);
me->add("force", -20);
}
             else {
           message_vision(HIY"\n$n�����������ò����ױܿ���һ�ֽ���"NOR,me,target);
me->receive_damage("sen", 10);
me->add("force", -20);
}
}
        if( !target->is_fighting(me) ) {
                if( living(target) ) {
                        if( userp(target) ) target->fight_ob(me);
                        else target->kill_ob(me);
}
}
    me->start_busy(3);
return 1;
}
