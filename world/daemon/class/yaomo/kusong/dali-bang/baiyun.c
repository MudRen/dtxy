//perform baiyun ������
//created by vikee
//2000.10
//modify by huarong 2003.11
#include <ansi.h>

inherit SSERVER;

string *baiyun= ({
BLINK""HIR"\nǧ����ˮǧ���£��������������졣"NOR,
BLINK""HIG"\n�ƾ�������������������������ᡣ"NOR,
BLINK""CYN"\ņ��һ������ϴ��Ц˼���ƾ�ɽ�ۡ�"NOR,
BLINK""MAG"\nԶ�Ϻ�ɽʯ��б, ��������˼ҡ�"NOR,
BLINK""HIY"\n�������첻�ɺ��������ڵز��ɹ¡�"NOR,
BLINK""HIB"\n����ң�������֣����°������˾���"NOR,
BLINK""HIM"\n�ƺ�Զ�ϰ��Ƽ䣬һƬ�³�����ɽ��"NOR,
BLINK""HIC"\n����δҪ�޵����������������ơ�"NOR,
BLINK""HIW"\n������Զᶣ�ҡҷ����ա�"NOR,
BLINK""RED"\n��ȥĪ���ʣ������޾�ʱ��"NOR,
});


int perform(object me, object target)
{
         
        string str;       
        if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      target->is_corpse()
        ||      target==me)
                return notify_fail("��Ҫ��˭ʩչ��һ�С������޾�����\n");

        if(!me->is_fighting())
                return notify_fail("�������޾���ֻ����ս����ʹ�ã�\n");

        if((int)me->query("max_force") < 500 )
                return notify_fail("�������������\n");

        if (me->query_skill_mapped("force")!="huomoforce")
                return notify_fail("�������޾���������ϻ�ħ�ķ�����ʹ�á�\n");
                
        if((int)me->query_skill("huomoforce",1) <50)
                return notify_fail("��Ļ�ħ�ķ����𻹲�����ʹ�����������޾�����\n");

     if((int)me->query("force") < 500 )
                return notify_fail("����������㣡\n");

        if((int)me->query("sen") < 500 )
                return notify_fail("��ľ����㣬û����ʩ���⹦��\n");

        if((int)me->query_skill("dali-bang", 1) < 50)
                return notify_fail("��Ĵ����������𻹲�����ʹ����һ�л������ѣ�\n");

        if( time()-(int)me->query_temp("baiyun_end") < 6 )
                return notify_fail("�����ö��˾Ͳ����ˣ�\n");

        me->delete("env/brief_message");
        target->delete("env/brief_message");

	message_vision(HIY"\n$N���һ�������������������͵ļ����˴�������ɱ�־�ѧ�������޾���!\n"NOR,me,target);
	me->set_temp("DLB_perform", 1);
        message_vision(baiyun[random(sizeof(baiyun))], me, target);
        message_vision(HIB+"\n>>>>>>>>>>>"+NOR, me, target);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"));
        message_vision(baiyun[random(sizeof(baiyun))], me, target);
        message_vision(HIB+"\n>>>>>>>>>>>"+NOR, me, target);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon")); 
        message_vision(baiyun[random(sizeof(baiyun))], me, target);
        message_vision(HIB+"\n>>>>>>>>>>>"+NOR, me, target);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"));
        message_vision(baiyun[random(sizeof(baiyun))], me, target);
        message_vision(HIB+"\n>>>>>>>>>>>"+NOR, me, target);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"));
	me->delete_temp("DLB_perform");
	if ( (target->query("eff_kee")<0 || (!living(target) && target->query("kee")<0)) && random(5)==1 )
        {
        	str=target->name()+HIM"��"+me->name()+HIM"�û����ش�"NOR+HIY+"�������޾���"
	            +HIM"����ȫ��ǽڣ���Ҳ����������ǰ��ʲôģ����";
        	message("channel:rumor",HIM"����Ѩ���硿ĳ�ˣ�"+str+"\n"NOR,users());
        }

        me->receive_damage("sen", 100);
        me->add("force", -100-(int)me->query_skill("dali-bang",1)/5);

        me->set_temp("baiyun_end",time());
        //me->start_busy(1+random(2));
        return 1;
}




