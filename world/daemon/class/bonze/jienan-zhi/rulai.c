// rulai jienan-zhi perform��������
// lestat 2001

#include <ansi.h>
#include <combat.h>
inherit SSERVER;

int perform(object me, object target)
{
      string msg, dodge_skill;                                
      int damage, jiali, attack, defense, p;
      object weapon = me->query_temp("weapon");
      int cd = 7;
      if( !target ) target = offensive_target(me);
     
      if( !target || !me->is_fighting(target) || !living(target) )
           return notify_fail("���������ơ�ֻ����ս���жԶ���ʹ�á�\n");        
      if(me->query("family/family_name") != "�Ϻ�����ɽ" )
                return notify_fail("�����Ķ�͵ѧ�����书��\n");
      if( (int)me->query_skill("jienan-zhi",1) < 150 )
           return notify_fail("��Ľ���ָ������죬����ʹ�÷����񹦡��������ơ���\n");
      
      if( (int)me->query_skill("unarmed",1) < 150 )
           return notify_fail("��Ļ����ַ�������죬����ʹ�÷����񹦡��������ơ���\n");

      if( (int)me->query_skill("lotusforce",1) < 150 )
           return notify_fail("�����̨�ķ��ȼ�����������ʹ�á��������ơ���\n");  
      
      if( (int)me->query_str() < 24 )
           return notify_fail("��������������ǿ������ʹ�á��������ơ���\n");
      
      if( (int)me->query("max_force") < 1200 )
           return notify_fail("�������̫��������ʹ�á��������ơ���\n");
      
      if( (int)me->query("force") < 1500 )
           return notify_fail("�������̫���ˣ��޷�ʹ�ó����������ơ���\n");   
       
      //if( (int)target->query_condition("dashouyin"))
      //     return notify_fail("�Է��������С��������ơ������ˣ�\n");   
                
      //if( objectp(weapon = me->query_temp("weapon")) )
      //     return notify_fail("��������ʹ�á��������ơ���\n");    
      
      if( me->query("lunhui_zhuanshi") > 4 )
		cd = 5;
      else if( me->query("lunhui_zhuanshi") > 1 )
      		cd = 6;
      if( time()-(int)me->query_temp("rulai_end") < cd )
                return notify_fail("��������Ϣ��˳��\n");
      me->set_temp("rulai_end",time());
      jiali = me->query("force_factor")+1;
      attack = me->query("combat_exp")/10000;
      defense = target->query("combat_exp")/15000;
      me->add_temp("apply/strength", jiali/5);
      target->add_temp("apply/dodge", -jiali);
      target->add_temp("apply/parry", -jiali); 
      //damage = me->query_skill("jienan-zhi", 1)/20 * jiali;
      //if(damage > 800) damage = 800;
      //message_vision(HIR"\n$NͻȻ��ɫ���죬����Ĭ��������ԣ�˫�۹ǽ�һ���죬��Ȼ�ڿն���������$n��ǰ��ȥ����һʽ"HIY"���������ơ�"BLU"��\n"NOR,me,target);
      //���� �� �� �� �� �ˡ���
      message_vision(HIY"\n$N˫�ֺ�ʮ������Ĭ��������ԣ�������������������\n"NOR,me,target);
      message_vision("\n"+BLINK+HIW"��"+NOR+HIR"\n$N����֮�ϣ��ֳ�һ�������\n"NOR,me,target);
      COMBAT_D->do_attack(me, target,weapon);
      message_vision("\n"+BLINK+HIW"��"+NOR+HIG"\n��������$Nü���֣�תΪ��ɫ��\n"NOR,me,target);
      COMBAT_D->do_attack(me, target,weapon);
      message_vision("\n"+BLINK+HIW"��"+NOR+HIY"\n��������$N���֣�תΪ��ɫ��\n"NOR,me,target);
      COMBAT_D->do_attack(me, target,weapon);
      message_vision("\n"+BLINK+HIW"��"+NOR+HIB"\n��������$N���֣�תΪ��ɫ��\n"NOR,me,target);
      COMBAT_D->do_attack(me, target,weapon);
      message_vision("\n"+BLINK+HIW"��"+NOR+HIM"\n��������$N�����תΪ��ɫ��\n"NOR,me,target);
      COMBAT_D->do_attack(me, target,weapon);
      message_vision("\n"+BLINK+HIW"��"+NOR+HIC"\n��������$N���֣�תΪ��ɫ��\n"NOR,me,target);
      COMBAT_D->do_attack(me, target,weapon);
      message_vision(HIW"\n������������$N���£�������ҫ�۵İ׹⣬ֻ��$N������ڿն�����$n��ǰ��ȥ����һʽ"HIY"���������ơ�"HIW"��\n"NOR,me,target);
//      if( attack > defense ) { 
      if( random( attack + defense ) > defense/2 || !living(target) ) 
      { 
      	 /*if( objectp(armor = target->query_temp("armor/cloth"))
      	    && armor->query("armor_prop/armor") < 600
      	    && damage > 100){
                	message_vision(HIY"ֻ���⶷�����ӡ����ӡ��$N��$n"HIY"�ϣ�Խ��Խ�󣬾�������÷��飬�ѳ�һ�����ڵ��ϣ�\n"NOR, target, armor);
                        armor->unequip();
                        armor->move(environment(target));
                        armor->set("name", "�����" + armor->query("name"));    
                        armor->set("value", 0);
                        armor->set("armor_prop/armor", 0);
                        target->reset_action();
                        }
         */
         damage = me->query_skill("unarmed")/2 + random(me->query_skill("force")/4);
         damage = damage * 6 + me->query_str();
         damage = damage - target->query_temp("apply/armor");
         if( damage < me->query_str() ) damage = me->query_str();
      	 message_vision(RED"\n$nֻ���û����ؿ�һ���ʹ���Ѿ���$N�����������������ǰ�أ�\n"NOR,me,target);
      	 target->apply_condition("dashouyin", 1+(me->query_str()));
      	 target->receive_damage("kee", damage,  me); 
         target->receive_wound("kee", damage/2, me);
         msg = COMBAT_D->damage_msg(damage, "����");
         message_vision(msg, me, target);
         me->add("force", -damage/4);
	 COMBAT_D->report_status(target, 1);
	     }
       else 
       {
      	 dodge_skill = target->query_skill_mapped("dodge");
	       if( !dodge_skill ) dodge_skill = "dodge";
         message_vision(SKILL_D(dodge_skill)->query_dodge_msg(target, 1), me, target);
         me->add("force", -100);
        }
//      me->add("force", -200);
      me->start_busy(1+random(2));
      me->add_temp("apply/strength", -jiali/5);
      target->add_temp("apply/dodge", jiali);
      target->add_temp("apply/parry", jiali);

      return 1;
}

 

