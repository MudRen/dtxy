#include <ansi.h>

inherit SSERVER;

int perform(object me, object target)
{
int kar;
        object weapon;
        if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      target->is_corpse()
        ||      target==me)
                return notify_fail("��Ҫ��˭ʩչ��һ�С��������򡹣�\n");
       if  ((string)me->query("family/family_name") != "����ɽ���Ƕ�" )
                       return notify_fail("���ǧ�������ƺ����Ƿ���ɽ�洫��\n");  
        if(!me->is_fighting())
                return notify_fail("����������ֻ����ս����ʹ�ã�\n");

        if((int)me->query("max_force") < 1000 )
                return notify_fail("�������������\n");

        if((int)me->query("force") < 1000 )
                return notify_fail("����������㣡\n");

        if((int)me->query("sen") < 500 )
                return notify_fail("��ľ����㣬û����ʩ���⹦��\n");
        if((int)me->query_skill("qianjun-bang",1) < 100)
                return notify_fail("���ǧ�������𻹲�����ʹ����һ�л������ѣ�\n");

if( time()-(int)me->query_temp("xiao_end") < 6 )
return notify_fail("�����ö�Ͳ����ˣ�\n");

        me->delete("env/brief_message");
        target->delete("env/brief_message");

kar=me->query("force_factor");
message_vision(HIC"\n$N���㾫������һת��������������$n���������У�\n"NOR,me,target);
        me->add_temp("apply/dodge",kar/2);
        me->add_temp("apply/damage",kar/2);
        me->add_temp("apply/attack",kar/2);
        me->set_temp("QJB_perform", 4);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"));
        me->set_temp("QJB_perform", 1);  
        COMBAT_D->do_attack(me, target, me->query_temp("weapon")); 
        me->set_temp("QJB_perform", 6);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"));
        me->delete_temp("QJB_perform");
        me->add_temp("apply/dodge",-kar/2);
        me->add_temp("apply/damage",-kar/2);
        me->add_temp("apply/attace",-kar/2);
        me->receive_damage("sen", 300);
        me->add("force", -100);
        remove_call_out("perform2");
        call_out("perform2",2, me, target);
        message_vision(HIC"\n$N��������׼��������һ�ι�����\n"NOR,me,target);  
//        me->set_temp("fc_pfm_busy",1)
     me->set_temp("xiao_end",time());
        return 1;
}

void remove_effect(object me) {
  if (!me) return;
  me->delete_temp("fc_pfm_busy");
}

int perform2(object me, object target)
{
        int kar,tkar;
        string wep;
        if (!me) return 1;
        if(!target) return 1;
        remove_call_out("remove_effect");
                call_out("remove_effect", random(5)+2, me);
        if(!living(target)) return notify_fail("�����Ѿ�������ս���ˡ�\n");
        if(!objectp(wep = me->query_temp("weapon")) || wep->query("skill_type") != "stick"){
        if(!wep)message_vision(HIY"$N����������ʧ��ʹ����ʣ�µĹ����ˣ�$n�������˿�����\n"NOR,me,target);
        else  message_vision(HIY"$N����"+wep->name()+HIY"��ֹͣ׷����$n�������˿�����\n"NOR,me,target);
        return 1;}
        kar=me->query("force_factor");
        tkar=target->query("force_factor");
        message_vision(HIC"\n$N��������֮���������ҳ��棬�ִ��һ�С�\n"NOR,me,target);
        if(random(kar+tkar)>tkar) 
        {
              target->start_busy(random(2));
              me->set_temp("QJB_perform",8);
              COMBAT_D->do_attack(me, target, me->query_temp("weapon"),0);
              me->add("force", -100);
              me->delete_temp("QJB_perform");
       }
       if((me->query("combat_exp")/20000+me->query_skill("stick")+me->query_skill("qianjun-bang"))
             >random(target->query("combat_exp")/20000+target->query_skill("dodge")))
        {       
                message_vision(HIR"\n$N������Ƶ�,��Ȼ����ס��,"+wep->name()+"���Ʋ����˵ؽ�����\n"NOR,me,target);
                target->receive_damage("kee", me->query_skill("stick")/3);
                target->receive_wound("kee", me->query_skill("stick")/6);
                COMBAT_D->report_status(target);
                me->add("force",-200);
           }
        if( !target->is_fighting(me) ) {
                if( living(target) ) {
                        if( userp(target) ) target->fight_ob(me);
                        else target->kill_ob(me);
                }
        }

        me->start_busy(3);
}
