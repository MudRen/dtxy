#include <ansi.h>
#include <condition.h>
#include "/daemon/skill/eff_msg.h";
inherit F_CLEAN_UP;

int update_condition(object me, int duration)
{

      int damage, p;
      string msg;
      
      damage = me->query_condition("dashouyin")/5 +2;
//      damage *= me->query_con();
      damage += me->query_con(); // emotion
      
      tell_object(me, "ͻȻ��о��ؿ���ʹ�쳣���ղű������������е��߹Ǵ�����Ҫ�ѿ����Ƶģ���ѪҲ�ӿ������˳�����\n");
      tell_room(environment(me), HIR + me->name()+"ͻȻһ�Բ�����˫�����أ��ŵ��㵹���������������۵�һ���³�����Ѫ����\n" NOR,({ me }));
      me->receive_damage("kee", damage/2);
      me->receive_wound("kee", damage/2);
      p = (int)me->query("kee")*100/(int)me->query("max_kee");
      msg = "( $N"+eff_status_msg(p)+" )\n";
      if(living(me)) 
             message_vision(msg, me);
 //     me->set_temp("last_damage_from", "�������ƾ�������");
	  me->set_temp("death_msg","�����������ˡ�\n");
      me->apply_condition("dashouyin", duration - 1);
	  if( duration < 1 ) return 0;
   return CND_CONTINUE;
}

string query_type(object me)
{
	return "hurt";
}

