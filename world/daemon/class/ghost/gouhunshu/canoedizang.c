// dizang.c
// hell �ķ���

// fixed overflow issue by emotion 04/28/2006

#include <ansi.h>

inherit SSERVER;

int cast(object me, object target)
{
        string msg;
        int damage;
        float ap, dp;

        if( !target ) target = offensive_target(me);
        if(me->query("family/family_name")!="���޵ظ�")
                return notify_fail("�㲻�ǵظ����ӣ�����ʹ������ܣ�\n");

        if( !target
        ||      !target->is_character()
        ||      target->is_corpse()
        ||      target==me)
                return notify_fail("��Ҫ��ز������Ʋ�˭��\n");

        if((int)me->query("mana") < 200+(int)me->query("mana_factor") )
                return notify_fail("��ķ���������\n");

        if((int)me->query("sen") < 50 )
                return notify_fail("���޷����о��������ز�������\n");

        me->add("mana", -100-(int)me->query("mana_factor"));
        me->receive_damage("sen", 50);

        if( random(me->query("max_mana")) < 100 ) {
                write("��ʧ���ˣ�\n");
                return 1;
        }

        msg = HIY
"$N�������˼������ģ��ϵ�����ز�������$N���С�\nһ�������еز����������ˡ����еĸ���������س���$n��\n" NOR;

        ap = 0.0+me->query_skill("spells");
        ap = ( ap * ap * ap / (4 * 400) ) * (int)me->query("sen");
        ap = ap+(int)me->query("combat_exp");
        dp = 0.0+target->query("combat_exp");
        if( (ap + dp)*random(1000)/1000 > dp /4) {
                damage = (int)me->query("max_mana") / 2 +
random((int)me->query("eff_sen") / 2);
                damage -= (int)target->query("max_mana") / 2 +
random((int)target->query("eff_sen") / 2);
                damage +=(int)me->query("mana_factor")-random((int)target->query("mana_factor"));
//here we can see if 2 players are at same status, the attacker has higher chance.
                if( damage > 0 ) {
//finally damage also depends on enabled spells level.
                damage +=random((damage*(int)me->query_skill("spells"))/100);
                        msg += HIC "���$n��������ţ�Ѫ���ɽ������˲��ᣡ\n" NOR;
                        target->receive_damage("sen", damage, me);
                        target->receive_wound("sen", damage/3, me);
                        target->receive_damage("kee", damage, me);
                        target->receive_wound("kee", damage/4, me);
                        me->improve_skill("gouhunshu", 1, 1);
                }
            else {
//here, cast failed and the target's mana_factor will be added to the previous
//damage to hurt yourself:(...note, damage<0.
                        msg += HIC "�����������$n�Է�������������������$N��\n" NOR;
                damage -= (int)target->query("mana_factor");
                damage -=random((-damage*(int)target->query_skill("spells"))/100);
                        me->receive_damage("sen", -damage, target);
                        me->receive_wound("sen", -damage/3, target);
                        me->receive_damage("kee", -damage, target);
                        me->receive_wound("kee", -damage/4, target);
           //             me->improve_skill("gouhunshu", 1, 1);
            }
             }
        else
                msg += "���Ǳ�$n�㿪�ˡ�\n";

        message_vision(msg, me, target);
        if( damage > 0 ) COMBAT_D->report_status(target);
        else if( damage < 0 ) COMBAT_D->report_status(me);
//damage=0 corresponding to "���Ǳ�$n�㿪�ˡ�\n"--no report.

        if( !target->is_fighting(me) ) {
                if( living(target) ) {
                        if( userp(target) ) target->fight_ob(me);
                        else
target->kill_ob(me);
                }
                me->kill_ob(target);
        }

        me->start_busy(2+random(2));
        return 1;
}

