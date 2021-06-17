//��Ϊxue.c
//������ѩ
//write by yesi
//yeahsi@21cn.com

#include <ansi.h>
inherit SSERVER;

void check(object me);
void pfmxue_effect(object me, object victim);
void remove_effect(object me);

int perform(object me)
{
        int skill;
        int sword_skill,snowsword_skill;
        
        skill = me->query_skill("xuanzong-force",1);
        if( skill > 250 ) skill=250;
        sword_skill= me->query_skill("sword",1);
        snowsword_skill= me->query_skill("huntian-jian",1);
                       
                               
        if( skill < 100 )  return notify_fail("��������ķ���Ϊ������\n");
        if( sword_skill < 80 )  return notify_fail("��Ļ�������δ�����졣\n");
        if( snowsword_skill < 120 )  return notify_fail("��Ļ���һ��δ�����졣\n");
        
        if( me->query_temp("pfmxue") ) 
          {remove_effect(me);return 1;}
          
        if (me->query_skill_mapped("force")!="xuanzong-force")
            return notify_fail("��������ѩ��������������ķ�����ʹ�á�\n");
        
        if(me->query("family/family_name") != "����ɽ���鶴")
               return notify_fail("[������ѩ]�����鲻��֮�ܣ�\n");     
        
        if( time()-(int)me->query_temp("pfmxue_end") < 10 )
                return notify_fail("����������������\n");       
               
        
        if( (int)me->query("force") < skill )     
                return notify_fail("�������������\n");
 
        me->add("force", -skill);
        message_vision(HIG "$N�������ķ�����������һ�ܣ�ֻ����ȫ����ƮƮ�ģ��ƺ��������Ʈ��\n" NOR, me);
        me->set_temp("pfmxue", 1);
        me->set_temp("pfmxue_time",skill);
        me->add_temp("apply/dodge",skill/6);
        me->set_temp("apply/sword",skill/6);
                   
        call_out("check", 1, me);
        return 1;
}


void check(object me)
{       
        object weapon;
        
         if(!me) return;
                
         if (me->query_skill_mapped("force") != "xuanzong-force"
                 || !objectp(weapon=me->query_temp("weapon")) 
                 || (weapon->query("apply/skill_type") != "sword" 
                     && ( weapon->query("skill_type") != "sword" && !me->is_manmade_npc()) ) 
                 ||  ( me->query_skill_mapped("sword") != "huntian-jian" && !me->is_manmade_npc()) )     
             remove_effect(me);
         else if(me->query_temp("pfmxue_time")<1)
             remove_effect(me);                 
         else {  me->add_temp("pfmxue_time",-1);
                call_out("check", 1, me);
              }
                     
}


void remove_effect(object me)
{
        int skill;
        if(!me) return;
        if(!me->query_temp("pfmxue"))
        	return;
        skill = me->query_skill("xuanzong-force",1);
        if( skill > 250 ) skill=250;
        remove_call_out("check");
        me->delete_temp("pfmxue");
        me->set_temp("pfmxue_end",time());
        me->add_temp("apply/dodge",-skill/6);
        me->delete_temp("apply/sword");
        tell_object(me, GRN"�㽫�����ķ��ջص��\n"NOR);
}

void pfmxue_effect(object me, object victim)
{   int damage,ini_damage_apply,skill,ini_attack_apply;
    string str;
    skill = me->query_skill("huntian-jian",1)/2; 
   
   if ( random(2)>0 )
          { ini_damage_apply = me->query_temp("apply/damage");
            ini_attack_apply = me->query_temp("apply/attack");
            me->add_temp("pfmxue",1);
            message_vision(HIG"\n$Nһ����գ��ڰ��������һŤ����$n�ֹ���һ�У�\n"NOR,me,victim);
            me->add_temp("apply/damage",30);
            me->add_temp("apply/attack",skill);
            damage = COMBAT_D->do_attack(me, victim, me->query_temp("weapon"));         
         
               
   if( damage <= 0 )
          {
          message_vision(HIG"\n$N����������������Ѹ����ת������һŤ�����潣Ʈ,�ڼ��������ܵĽǶ��ٶȳ��У�\n"NOR,me);
           me->add_temp("apply/damage",30);
           me->add_temp("apply/attack",skill);
           COMBAT_D->do_attack(me, victim, me->query_temp("weapon"));         
           me->add_temp("pfmxue",-1);
           }             
    else me->add_temp("pfmxue",-1);
    
    me->set_temp("apply/damage",ini_damage_apply);
    me->set_temp("apply/attack",ini_attack_apply);
          }
}
 

