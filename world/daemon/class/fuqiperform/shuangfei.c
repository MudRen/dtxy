#include <ansi.h>
inherit F_DBASE;
inherit SSERVER;
int perform(object me, object target)
{
 object weapon, victim = offensive_target(me);
 string msg;
        int ap,ap2,dp,damage;
object weapon2;

        if (!me->query("married"))
            return 0;
 if (!victim) return notify_fail("�����˭���С�����˫�ɡ���\n");
 if( !target )
  return notify_fail("������˭���С�����˫�ɡ���\n");
 if( target->query("id") == me->query("id") )
  return notify_fail("�������Լ����С�����˫�ɡ���\n");
 if( victim->query("id") == target->query("id") )
  return notify_fail("��������Ķ��ֽ��С�����˫�ɡ���\n");

if( me->query("gender") != "����" )
 {
  msg = "�ɷ�";
  //��������Լ����ɷ�Ļ�
  if( target->query("name") != me->query("husband/name")&& target->query("id") != me->query("couple/id") )
         return notify_fail("��ֻ�����ɷ���С�����˫�ɡ���\n");
 }
 else
 {
  msg = "����";
  //��������Լ����ɷ�Ļ�
  if( target->query("name") != me->query("wife/name")&& target->query("id") != me->query("couple/id") )
         return notify_fail("��ֻ�������ӽ��С�����˫�ɡ���\n");
 }
 if( !victim->is_character() || !me->is_fighting(victim) )
  return notify_fail("ֻ�ܶ�������ս���еĶ���ʹ�á�����˫�ɡ���\n");
 if( !target->is_fighting(victim) )
  return notify_fail("���"+msg+"���������ս���С�\n");

if( !objectp(weapon = me->query_temp("weapon")) ||!objectp(weapon2 = target->query_temp("weapon")) )
            return notify_fail("���ǿ�����ô������˫�ɡ�����\n");
 if( (int)target->query_temp("xingyue") )
  return notify_fail("��Ĵ�Ѿ���ʹ�á�����˫�ɡ��ˡ�\n");
 if( (int)me->query_temp("xingyue") )
  return notify_fail("���Ѿ���ʹ�á�����˫�ɡ��ˡ�\n");
 if((int)me->query("force") < 25+(int)me->query("force_factor") )
  return notify_fail("�������������\n");
 if((int)me->query("kee") < 100 )
  return notify_fail("�����Ѫ���㣬û����ʩ���⹦��\n");
if((int)target->query("force") < 25+(int)target->query("force_factor") )
return notify_fail("���"+msg+"����������\n");
 if((int)target->query("kee") < 100 )
  return notify_fail("���"+msg+"��Ѫ���㣬û����ʩ���⹦��\n");
 if( !(int)target->query_temp("xingyue_request") ) {
me->set_temp("xingyue_request", 1);
  tell_object(target, me->query("name")+"���㷢��������˫�ɡ�����\n");
tell_object(me,"����"+target->query("name")+"����������˫�ɡ�����\n");
  return 1;
 }
 target->delete_temp("xingyue_request");
 me->add("force", -25-(int)me->query("force_factor"));
 target->add("force", -25-(int)me->query("force_factor"));
 me->receive_damage("kee", 100);
 target->receive_damage("kee", 100);
msg = HIY "$N��$n���һЦ��������龡����ͷ������������ͨ��$N˫����㣬\n��
�ʵ������$n��ͷ�����˱���ңָ"+ victim->query("name") + "��"+victim->query("name") +"�е���ǰ��Ӱ��˸��\n
ʲô�������壡$N��$nͬʱ��ȣ����������Ͷȥ����һ�Ժ������������衣\n" NOR;
 if(me->query("gender") == "Ů��")
{
msg = replace_string(msg,"$N",me->query("name"));
msg = replace_string(msg,"$n",target->query("name"));
}
        else
{
msg = replace_string(msg,"$n",me->query("name"));
msg = replace_string(msg,"$N",target->query("name"));
}
tell_room(environment(me),msg);
ap = me->query_skill(weapon->query("skill_type"));
ap2 = target->query_skill(weapon2->query("skill_type"));
ap=ap*ap*ap/1000*me->query("kee");
ap += (int)me->query("combat_exp");
ap2 = ap2*ap2*ap2/1000*target->query("kee");
ap2 += (int)target->query("combat_exp");
ap = ap+ap2;
dp = victim->query("combat_exp");
        if( random(ap + dp) > dp ) {
damage=(int)me->query("max_force")/10+random((int)me->query("eff_kee")/5);
damage+=(int)target->query("max_force")/10+random((int)target->query("eff_kee")/5);
damage-=(int)victim->query("max_force")/10+random((int)victim->query("eff_kee")/5);
damage-=random((int)victim->query("force_factor"));
damage+=(int)me->query("force_factor")+(int)target->query("force_factor");
//here we can see if 2 players are at same status, the attacker has higher chance.
msg = "";
                if( damage > 0 ) {
msg += HIC "���"+victim->query("name")+"û�ж㿪����$N��$n͸�������\n" NOR;
                        victim->receive_damage("kee", damage, me);
victim->receive_wound("kee", damage/3, me);
                }
     else {
msg += HIC "���"+victim->query("name")+"���������У��Ų�һ����$N��$n�����Լ�
ײ��һ��\n" NOR;
          me->receive_damage("kee", me->query("kee")/4, victim);
me->receive_wound("kee",me->query("max_kee")/4, victim);
                        target->receive_damage("kee", target->query("kee")/4, victim);
target->receive_wound("kee", target->query("max_kee")/4, victim);

     }
             }
 else
msg = "���Ǳ�"+victim->query("name")+"�㿪�ˡ�\n";
msg =  replace_string(msg,"$N",me->query("name"));
msg = replace_string(msg,"$n",target->query("name")); 
tell_room(environment(me),msg);
        me->start_busy(2);
        target->start_busy(random(5));
 return 1;
}

