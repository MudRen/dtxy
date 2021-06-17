
#include <ansi.h>
#include <combat.h>

inherit SSERVER;

void feijian_ok(object);
void postfeijian(object,object,object,int);

mapping feijian= ([
       "damage": 60,
       "force" : 60,
       "dodge" : -80,
       "parry" : -50,
       "damage_type" : "����",
       "action" :  HIW"$w"+HIW"�ڿ��лó��������⣬����Ͷ�ְ㣬��$n��$l��ȥ"NOR,
       "post_action" : (: postfeijian :)
    ]);
mapping feijian1= ([
       "damage": 80,
       "force" : 80,
       "dodge" : -90,
       "parry" : -60,
       "damage_type" : "����",
       "action" :  HIW"$w"+HIW"�ڿ���һ��ת�ۣ��ٶȶ�Ȼ�ӿ죬���������$n��$l"NOR,
       "post_action" : (: postfeijian :)
    ]);

int perform(object me, object target)
{
      object weapon=me->query_temp("weapon");
      if(!wizardp(me) && me->query("family/family_name")!="��ѩɽ")
          return notify_fail("[����Ͷ��]ֻ��ѩɽ���Ӳſ����ã�\n");
      if( !target ) target = offensive_target(me);
      if( !target || !target->is_character()||target->is_corpse()||target==me)
          return notify_fail("��Ҫ����˭��\n");
      if (!target->is_fighting(me))
             return notify_fail("����û���ڴ�ܣ�\n");
      if (me->query_temp("no_feijian") )
          return notify_fail("������״̬���ѣ�����ʹ�÷ɽ���\n");      
      if (me->query_skill("ningxie-force",1)<120)
          return notify_fail("����ڹ�̫����ɳ�ȥ�϶��ɲ�������\n");
      if (me->query_skill("bainiao-jian",1)<120) 
          return notify_fail("��İ��񽣷���ô�ã����İѽ����Լ����ϡ�\n");
    if (me->query_skill("throwing",1)<120)
        return notify_fail("��İ�������̫����Ұѽ��ӳ�ȥ���϶��Ҳ���Ŀ�ꡣ\n");
      if (me->query("force")<600)
           return notify_fail("���������̣����Լ����ɽ���\n");
     me->delete("env/brief_message");
   target->delete("env/brief_message");
      me->add("force", -100);
      me->set("actions",feijian);
    message_vision(HIW"$NͻȻ��Хһ��������"+weapon->query("name")+HIW"���ֶ���������һ�����磬ֱ��$n��ȥ��"NOR,me,target);
      COMBAT_D->do_attack(me, target, me->query_temp("weapon"));
      me->set_temp("no_feijian",1);
      call_out("feijian_ok",2+random(2),me);
      me->reset_action();
      return 1;
}

void feijian_ok(object me) {
      int count, damage;
      if (!me) return;
      me->delete_temp("no_feijian");
      count = me->query_temp("feijian_count");
      damage = (1 + count) * count * 5;
      me->add_temp("apply/damage", -damage);
      me->delete_temp("feijian_count");
}

void postfeijian(object me,object victim,object weapon, int damage) {
      int count;
      if (damage > 0 || damage == RESULT_DODGE || damage == RESULT_FORCE )
         message_vision(HIW""+weapon->query("name")+HIW"�ڿ��д��˸�ת���ַɻص�$N���С�\n"NOR,me);
      else {
      	   me->add_temp("feijian_count", 1);
      	   count = me->query_temp("feijian_count");
           //message_vision(HIW""+weapon->query("name")+HIW"�ı䷽�򣬡�ৡ���һ����бб���ڵ��ϡ�\n"NOR,me);
           message_vision(HIY""+weapon->query("name")+HIY"��Ծ�ڰ�ա�\n"NOR,me,victim);
           //if( me->is_busy() && !victim->is_busy() ) victim->start_busy(1);
           //me->start_busy(1);
           me->set("actions",feijian1);
           me->add_temp("apply/damage", count * 10);
           COMBAT_D->do_attack(me, victim, me->query_temp("weapon"));
           me->reset_action();
           //weapon->move(environment(me));
      }
}
