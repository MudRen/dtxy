
//ningxie-force��Ѫ��
#include <ansi.h>
inherit SSERVER;
int exert(object me, object target)
{
        int lvl,lvl2;
        int damage;
        if(!wizardp(me) && me->query("family/family_name")!="��ѩɽ")
          return notify_fail("������Ѫ��ֻ��ѩɽ���Ӳſ����ã�\n");
        if( !me->is_fighting(target) )
                return notify_fail("ֻ����ս���жԵ���ʹ�ã�\n");
        lvl = me->query_skill("ningxie-force",1);
    if(!target)target = offensive_target(me);
if(target==me) target = offensive_target(me);
        if( (int)me->query("force") < 500 )
                return notify_fail("�������������\n");
         if( time()-(int)me->query_temp("ningxie_end") < 6 )
          return notify_fail("��������񹦣���Ϣ��˳��\n");
        if( lvl < 100 )
return notify_fail("��ġ�������Ѫ�������̫ǳ���ò�������Ѫ�󷨡���\n");
lvl = me->query_skill("force")*me->query("force")/me->query("max_force");
if(target->query_skill("force")&&target->query("max_force")&&(target))
lvl2 = target->query_skill("force")*target->query("force")/target->query("max_force");
else lvl2=0;
damage = me->query_skill("ningxie-force",1);
damage = damage + random(damage);
message_vision(HIW+"$N��ɫһ������������ѩ��ĺ�����\n"+NOR,me);
if(random((me->query("combat_exp")))>(int)target->query("combat_exp")/3 )
{
         me->set_temp("ningxie_end",time());
         message_vision(
                HIW +
"$N������������$n�����ĺ����������ţ�$N��ȫ�������ˣ�\n"+NOR,target,me);
target->receive_wound("kee",damage,me);
COMBAT_D->report_status(target,1);
target->start_busy(lvl/(lvl2+1)+1);
}
else
{
         me->set_temp("ningxie_end",time()-3);
         message_vision(
                HIW +
"$N����Σ�գ����м��ˣ��㿪�˴�ʽ��\n"+NOR,target);
}
        me->add("force", -damage/(2+random(2)));
me->start_busy(1+random(2));
return 1;
}
