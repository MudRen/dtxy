// ningxie.c
//write by yeahsi
//yeahsi@21cn.com

#include <ansi.h>
#include <combat.h>
inherit SSERVER;
//inherit F_CLEAN_UP;

void remove_effect(object me,object target, int dodge_amount,int attack_amount);
void check(object me,object target,int dodge_amount,int attack_amount);
void ningxie_result(object me,object target,int dodge_amount,int attack_amount);

int perform(object me, object target)
{
        int skill,skill_blade, skill_dodge, dodge_amount,attack_amount;
        int blade_skill,bingpo_skill;
        object weapon;

        weapon=me->query_temp("weapon");
        skill = me->query_skill("ningxie-force",1);
        blade_skill= me->query_skill("blade",1);
        bingpo_skill= me->query_skill("bingpo-blade",1);
        if( skill > 250 ) skill=250;
        skill_dodge = me->query_skill("dodge",1);
        skill_blade = me->query_skill("force",1);
        attack_amount=skill_blade/10;
        dodge_amount=skill_blade/10;


        if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      target->is_corpse()
        ||      target==me)
                return notify_fail("��Ҫ��˭ʩչ����Ѫ����\n");

        if(!me->is_fighting())
               return notify_fail("����Ѫ��ֻ����ս����ʹ�ã�\n");
        if(!wizardp(me)&&(string)me->query("family/family_name") != "��ѩɽ" )
   		return notify_fail("��ı��Ǻ����Ǵ�����͵ѧ���ģ�\n");
        if( skill < 100 )  return notify_fail("��ı�����Ѫ����Ϊ������\n");
        if( blade_skill < 100 )  return notify_fail("��Ļ�������δ�����졣\n");
        if( bingpo_skill < 100 )  return notify_fail("��ı��Ǻ���δ�����졣\n");


        if( me->query_temp("ningxie") )
            {remove_effect(me, target, dodge_amount, attack_amount);return 1;}

        if( (int)me->query("force") < skill )
                return notify_fail("�������������\n");



        me->add("force", -skill);
        message_vision(HIW "$N����Ѫ����������ת��Ȼ������ע��"+weapon->name()+HIW"�С�
$N����"+weapon->name()+HIW"������������һ�����̣���Բ�����ڵĿ�����������������\n" NOR, me);
        me->set_temp("ningxie", 1);
        target->set_temp("ningxie_effect",0);

        //Ҫperform ningxie��ȻҪ��������
        me->add_temp("apply/blade", attack_amount);
        me->add_temp("apply/damage",dodge_amount);

        call_out("remove_effect",skill,me,target,dodge_amount,attack_amount);
        call_out("ningxie_result",2+random(2),me,target,dodge_amount,attack_amount);
        call_out("check", 1, me,target,dodge_amount,attack_amount);
        return 1;
}


void check(object me,object target, int dodge_amount,int attack_amount)
{
        object weapon;
	if(!me) return;
        if(!objectp(target))  remove_effect(me, target, dodge_amount, attack_amount);
        else if( !living(target) || !present(target->query("id"), environment(me)) )
                remove_effect(me, target, dodge_amount, attack_amount);

        else if(!present(target->query("id"), environment(me))
                || !me->is_fighting(target) || !me->is_fighting() )
                remove_effect(me, target, dodge_amount, attack_amount);


        else if (me->query_skill_mapped("force") != "ningxie-force"
                 || !objectp(weapon=me->query_temp("weapon"))
                 || (weapon->query("apply/skill_type") != "blade"
                     && weapon->query("skill_type") != "blade" )
                 ||  me->query_skill_mapped("blade") != "bingpo-blade" )
             remove_effect(me, target, dodge_amount, attack_amount);

        else call_out("check", 1, me,target,dodge_amount,attack_amount);

}


void remove_effect(object me,object target, int dodge_amount,int attack_amount)
{
        if(!me) return;
        if( !me->query_temp("ningxie") ) return;
        remove_call_out("check");
        remove_call_out("remove_effect");
        remove_call_out("ningxie_result");
        me->add_temp("apply/damage", -dodge_amount);
        me->delete_temp("apply/blade");
        me->delete_temp("ningxie");
        tell_object(me, GRN"�㽫��Ѫ���ջص��\n"NOR);
        message_vision(HIY"��Χ��������ɢ���ˡ�\n"NOR,me);
        tell_object(target, HIY"�����ů�������ˡ�\n"NOR);
  if(living(target)) target->delete_temp("ningxie_effect");
}


void ningxie_result(object me,object target,int dodge_amount,int attack_amount)
{
           float afp,vfp,mod_val;
           object weapon;
           string str;
           if(!me) return;
           if(!objectp(target)) return;
           if( !present(target->query("id"), environment(me)) || !me->is_fighting(target) || !me->is_fighting() )
           {
                remove_effect(me, target, dodge_amount, attack_amount);
                return;
           }
           weapon=me->query_temp("weapon");

            message_vision(HIB"\n����$N����"+weapon->name()+HIB"���趯����Χ�Ŀ���Խ��Խ���ˡ�\n"NOR,me);

            afp = COMBAT_D->skill_power(me, "force", SKILL_USAGE_DEFENSE);
            if( afp < 1) afp = 1.0;
            vfp = COMBAT_D->skill_power(target, "force", SKILL_USAGE_ATTACK);
            if( vfp < 1 ) vfp = 1.0;
            if( me->query("force_factor") && (me->query("force") > me->query("force_factor")) )
                   mod_val = (100.0+me->query("force_factor")/10);
                   else mod_val=100.0;
            if( afp > 1000000 )     mod_val = afp / 100 * (100 + mod_val);
                     else   mod_val = (100 + mod_val) * afp / 100;
            if( mod_val < 1 ) mod_val = 1.0;

            if( (mod_val + vfp)*random(1000000)/1000000 < vfp )
                  {message_vision(YEL"$N����һת��ȫ���Ѻ���������ϣ�\n"NOR,target);
                   target->add_temp("ningxie_effect",-1);
                   if ( target->query_temp("ningxie_effect") < 0 )  target->set_temp("ningxie_effect",0);
                  }

                else{      if( me->query("force_factor") && (me->query("force") > me->query("force_factor")) )
                                 me->add("force",-me->query("force_factor"));

                        switch (target->query_temp("ningxie_effect"))
                          {
                                case 0: {message_vision(WHT"$N����һ��������\n"NOR,target);
                                         me->set_temp("piaoxue",1+random(3));
                                         COMBAT_D->do_attack_damage(me, target, me->query_temp("weapon"));
                                         COMBAT_D->report_status(target);
                                         target->receive_damage("sen",random(me->query_skill("force")));
                                         COMBAT_D->report_sen_status(target);
                                         target->add_temp("ningxie_effect",1);
                                         me->delete_temp("piaoxue");
                                         break;
                                        }

                                case 1: { message_vision(WHT"$N��Ļ��������\n"NOR,target);
                                          me->set_temp("piaoxue",4+random(2));
                                          COMBAT_D->do_attack_damage(me, target, me->query_temp("weapon"));
                                          COMBAT_D->report_status(target);
                                          target->receive_damage("sen",random(me->query_skill("force")));
                                          COMBAT_D->report_sen_status(target);
                                          target->add_temp("ningxie_effect",1);
                                          me->delete_temp("piaoxue");
                                          break;
                                         }

                                case 2:  {message_vision(WHT"$N�����ɫ�Ұף�\n"NOR,target);
                                          me->set_temp("piaoxue",6+random(2));
                                          COMBAT_D->do_attack_damage(me, target, me->query_temp("weapon"));
                                          COMBAT_D->report_status(target);
                                          target->receive_wound("sen",random(me->query_skill("force")));
                                          COMBAT_D->report_sen_status(target);
                                          target->add_temp("ningxie_effect",1);
                                          me->delete_temp("piaoxue");
                                          break;
                                         }

                                case 3:  {message_vision(WHT"$N�����һ�������ˣ�\n"NOR,target);
                                          me->set_temp("piaoxue",8+random(2));
                                          COMBAT_D->do_attack_damage(me, target, me->query_temp("weapon"));
                                          COMBAT_D->report_status(target);
                                          target->receive_wound("sen",random(me->query_skill("force")));
                                          COMBAT_D->report_sen_status(target);
                                          me->delete_temp("piaoxue");
                                         }

                        }
                    if (target->query("eff_kee")<0 || target->query("eff_sen")<0 || (!living(target) && ((target->query("sen")<0) || target->query("kee")<0)) )
                       {str=target->name()+"��"+me->name()+"����"+weapon->name()+HIM"�������ĺ��������ˣ���˵��ʬ��Ҳ��һ����һ��ģ�"NOR;
                        CHANNEL_D->do_channel(me, "rumor",str);
                        target->die();
                        me->delete_temp("last_channel_msg");
                       }
                    }

             if ( me->query_temp("ningxie") )  call_out("ningxie_result",3+random(2),me,target,dodge_amount,attack_amount);
}
