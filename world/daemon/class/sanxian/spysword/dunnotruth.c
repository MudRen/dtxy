// �����ɵ� �ǳ�����dunnotruth
// created by mind 2001/2
// /daemon/class/sanxian/spysword/dunnotruth.c

#include <ansi.h>

inherit SSERVER;
int perform(object me, object target)
{
        int damage,k,delay;
        string msg;
        object weapon=me->query_temp("weapon");
        if( !target ) target = offensive_target(me);
        
//if(!me->query("m_success/������ƪ"))
//                return notify_fail("�㲻�ὣ���ܴ�������\n");
        if( !target || !target->is_character() || !me->is_fighting(target) )
                return notify_fail("�㲻��ս���С�\n");
                
        if( (int)me->query_skill("spysword",1)< 150)
        return notify_fail("��Ĵ̿ͽ���������졣\n");
        if(!wizardp(me) && me->query("family/family_name")!="����ɢ��" )
        return notify_fail("�������͵���ľ��У�\n");
                        
        if( (int)me->query("force")<1500)
        return notify_fail("����������̫��������ʹ�á����ɵ� �ǳ�������\n");
        if(me->query_temp("have_pfm"))
        return notify_fail("���չʩ��������ʽ����Ϣ��û����������\n");
        if (me->query("betrayer") || me->query("betray/count"))
           return notify_fail("���Ķ����ߺ�������ɢ�ɵľ������ڡ�\n");
        
        me->set_temp("have_pfm",1);

        msg = HIB "\n$NͻȻ����һ�䣬���е�"+ weapon->query("name")+ HIB"��Ӱ���٣������籡�������Ľ�����\n"NOR;
        k=me->query("old_flag/jiandao");
        if(!k||k==0)    k=4;
        delay=0;
        message_vision(msg, me, target);
        if( random(me->query_skill("sword")) > target->query_skill("force",1)/3 )
        {
        	msg = WHT "\n$nֻ���ý���Ϯ�壬��ʱ��֫��ľ�������á�\n"NOR;
        	message_vision(msg, me, target);
        	delay = 3+random(k);
        	if( delay > 5 ) delay = 5;
        	target->start_busy(delay);
        	me->add("force",-100);
        }
        if(random(me->query("combat_exp"))>target->query("combat_exp")/4)
        {
        	damage = me->query_skill("sword") * (k-delay);
        	damage = damage/2+random(damage/3);
        	damage = damage - target->query_temp("apply/armor");
	        if(damage<me->query_skill("spysword",1))    damage=me->query_skill("spysword",1);
	        //if( damage>500) damage=500;
	                
	        target->receive_damage("kee",damage,me);
	        target->receive_wound("kee",damage/3,me);
	        me->add("force",-damage/5);
	        if( wizardp(me) ) tell_object(me,HIY"\ndamage : " + damage + "��\n"NOR);
	        if( (int)me->query("force")<0)  me->set("force",0);
	        
	        if( damage < 200 ) msg = HIY"\n���$n�ؿ�һʹ���ƺ�һ����\n"NOR;
	        else if( damage < 300 ) msg = HIY"\n���$n��$N���м��������١���һ������������\n"NOR;
	        else if( damage < 500 ) msg = RED"\n���$n��$N���صĽ���Ϯ�У������ܵ������ش�����������������\n"NOR;
	        else msg = HIR"\n���$n��$N�ġ����ɵ� �ǳ������������ģ���ǰһ�ڣ��������ɳ�������\n"NOR;
	        message_vision(msg, me, target);
	        COMBAT_D->report_status(target,0);
	        /*if(random(me->query("combat_exp"))>target->query("combat_exp")/k && k>8 && random(me->query_kar())>30) {
	                        
	                        msg += HIG "\n$N�в�΢�ƣ�"+ weapon->query("name")+ HIG"�鶯�쳣��";
	                        msg += HIG"�ڽ����Ѿ�����������֮�ʣ���������������ɱ����\n" NOR;
	                        me->start_busy(4+random(2));
	                        me->start_call_out( (: call_other, __FILE__, "kill_him", me, target :), random(2)+4);
	        }*/               
        } 
        else 
        {
                msg = CYN"\n˭֪$n����������������$N�����Ľ������������ˡ�\n"NOR;
                me->add("force",-100);
                message_vision(msg, me, target);
        }
        me->start_busy(1);
        call_out("do_reset",delay+1+random(2),me);
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
   str=target->name()+"Ī����������ˣ�ȫ������û��˿���ۼ����ѵ�"+target->name()+HIM"���ڣ����������������ֳ�����"+NOR+HIW"����"+NOR+HIM"�ش����ӡ�";
        message("channel:rumor",HIM"����Ѩ���硿ĳ�ˣ�"+str+"\n"NOR,users());   
                message_vision(msg, me, target);
                target->heart_beat();
        }
        return ;
}
