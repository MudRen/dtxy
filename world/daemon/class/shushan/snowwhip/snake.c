#include <ansi.h>
#include <combat.h>
inherit SSERVER;
void snake_ok(object);
int perform(object me, object target)
{
        object weapon;
        if( !target ) target = offensive_target(me);
        if( !target
        ||      !target->is_character()
        ||      target->is_corpse()
        ||      target==me)
                return notify_fail("��Ҫ��˭ʩչ��һ�С����ߡ���\n");
if(me->query("family/family_name")!="��ɽ��")
                return notify_fail("�㲻����ɽ���ӣ�����ʹ������ܣ�\n");
        if(!me->is_fighting())
                return notify_fail("�����ߡ�ֻ����ս����ʹ�ã�\n");
        if((int)me->query("max_force") < 500 )
                return notify_fail("�������������\n");
          if((int)me->query("force") < 500 )
                return notify_fail("����������㣡\n");
        if((int)me->query("sen") < 200 )
                return notify_fail("��ľ����㣬û����ʩ���⹦��\n");
        if((int)me->query_skill("snowwhip", 1) < 100)
                return notify_fail("��ĺ�ѩ�޷�����������ʹ����һ�л������ѣ�\n");
          if(me->query_temp("no_snake"))
                        return notify_fail("�����㺹��������ӣ��Ȼ�����ðɣ�\n");
        me->delete("env/brief_message");
        target->delete("env/brief_message");
message_vision(HIC"\n$N���б��Һ�Ȼ̧��������֮�����$n\n"NOR,me,target);
me->set_temp("SS_perform", 7);  
        COMBAT_D->do_attack(me, target, me->query_temp("weapon")); 
        me->delete_temp("SS_perform");
        me->receive_damage("sen", 50);
me->add("force", -50);
        me->set_temp("no_snake",1);
                call_out("snake_ok",1+random(2),me);
        if( !target->is_fighting(me) ) {
                if( living(target) ) {
                        if( userp(target) ) target->fight_ob(me);
                        else target->kill_ob(me);
}
}
return 1;
}
void snake_ok(object me)
{ if (!me) return;
      me->delete_temp("no_snake");
}
