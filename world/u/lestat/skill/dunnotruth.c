// �����ɵ� �ǳ�����dunnotruth
// created by mind 2001/2
// /daemon/class/sanxian/spysword/dunnotruth.c

#include <ansi.h>

inherit SSERVER;
int perform(object me, object target)
{
        int damage,k;
        string msg;
        object weapon=me->query_temp("weapon");
        if( !target ) target = offensive_target(me);
        
//if(!me->query("m_success/������ƪ"))
//                return notify_fail("�㲻�ὣ���ܴ�������\n");
        if( !target || !target->is_character() || !me->is_fighting(target) )
                return notify_fail("�㲻��ս���С�\n");
                
        if( (int)me->query_skill("spysword",1)< 150)
        return notify_fail("��Ĵ̿ͽ���������졣\n");
        if(me->query("family/family_name")!="����ɢ��")
        return notify_fail("�������͵���ľ��У�\n");
                        
        if( (int)me->query("force")<200)
        return notify_fail("����������̫��������ʹ�á����ɵ� �ǳ�������\n");
        if(me->query_temp("have_pfm"))
        return notify_fail("���չʩ��������ʽ����Ϣ��û����������\n");
        if (me->query("betrayer") || me->query("betray/count"))
           return notify_fail("���Ķ����ߺ�������ɢ�ɵľ������ڡ�\n");
        
        me->set_temp("have_pfm",1);

        msg = HIB "$NͻȻ����һ�䣬���е�"+ weapon->query("name")+ HIB"��Ӱ���٣������籡�������Ľ�����\n"NOR;
        k=me->query("old_flag/jiandao");
        if(!k||k==0)    k=3;
        if(random(me->query("combat_exp"))>target->query("combat_exp")/k)
        {

        target->start_busy(1+random(2));
        me->start_busy(3);
        damage=(me->query_str()-target->query_con())*random(me->query_cor());
        if(damage<0)    damage=10;
        if( damage>500) damage=500;
                
        target->receive_damage("kee",damage,me);
        target->receive_wound("kee",damage/3,me);
        me->add("force",-damage/5);
        if( (int)me->query("force")<0)  me->set("force",0);
        
        if( damage < 40 ) msg += HIY"���$n�ؿ�һʹ���ƺ�һ����\n"NOR;
        else if( damage < 60 ) msg += HIY"���$n��$N���м��������١���һ������������\n"NOR;
        else if( damage < 120 ) msg += RED"���$n��$N���صĽ���Ϯ�У������ܵ������ش�����������������\n"NOR;
        else msg += HIR"���$n��$N�ġ����ɵ� �ǳ������������ģ���ǰһ�ڣ��������ɳ�������\n"NOR;
        if(random(me->query("combat_exp"))>target->query("combat_exp")/k && k>8 && random(me->query_kar())>30) {
                        
                        msg += HIG "\n$N�в�΢�ƣ�"+ weapon->query("name")+ HIG"�鶯�쳣��";
                        msg += HIG"�ڽ����Ѿ�����������֮�ʣ���������������ɱ����\n" NOR;
                        me->start_busy(4+random(2));
                        me->start_call_out( (: call_other, __FILE__, "kill_him", me, target :), random(2)+4);
        }               
        } else 
        {
        me->start_busy(1);
        me->add("force",-10);
                msg += CYN"����$n������$N����ͼ����û���ϵ���\n"NOR;
        }
        message_vision(msg, me, target);
        call_out("do_reset",3,me);
        return 1;
}

void do_reset(object me)
{
        if( !objectp(me))       return;
        if( (int)me->query_temp("have_pfm"))
                me->delete_temp("have_pfm");
}

void kill_him(object me, object target)
{
        string msg,str;
if(!living(target)) 
      return;
        
        if(me->is_fighting() && target->is_fighting() &&
        environment(me) == environment(target))
        {
                msg =HIR"\n$nֻ���ý���Ϯ�壬�۾���ʱ������ͻ�˳�������\n" NOR;
                target->receive_damage("sen",target->query("max_sen")+1,me);
                target->receive_wound("sen", (int)target->query("max_sen")+1, me);
                target->receive_damage("kee",target->query("max_kee")+1,me);
                target->receive_wound("kee", (int)target->query("max_kee")+1, me);
                msg+=HIR"\n$N����$n��ʬ�壬����̾�˿�����������\n" NOR;
                COMBAT_D->report_status(target);
                str=target->name()+"Ī����������ˣ�ȫ������û��˿���ۼ���\n�ѵ�"+target->name()+"���ڣ����������������ֳ����˽����ش����ӡ�";
        message("channel:rumor",HIM"����Ѩ���硿ĳ�ˣ�"+str+"\n"NOR,users());   
                message_vision(msg, me, target);
                target->heart_beat();
        }
        return ;
}
