#include <ansi.h>
inherit ITEM;
string money_str(int amount);
int pay_player(object who, int amount);
int help(object me);
void create()
{
        set_name(HIY"���ƽ�����"NOR, ({"master card","card"}) );
        set_weight(10);
        set("no_drop","��ô���صĶ�����ô�ܶ����ء�\n");
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("material", "steal");
                set("long", "
            [1;33m    ���ƽ�����(Master card)[m
��������������������������������������������������������������
��               [0;1;37;40m  ������ʹ���������[m                        ��
��     ȡǮ��    �����ʽ��cardwithdraw <����> <���ҵ�λ>   ��
��     ȡǱ�ܣ�  �����ʽ��cardwithdraw <����> Ǳ��         ��
��     ��Ǯ��    �����ʽ��carddeposit  <����> <���ҵ�λ>   ��
��     ��Ǳ�ܣ�  �����ʽ��carddeposit  <����> Ǳ�ܡ�       ��
��     ��ѯ�������ʽ��cardbalance                         ��
��     [0;1;37;34m�������ε�ͨ�����ÿ������������ڱ�վ�������� [m        ��
��������������������������������������������������������������
ע��: ��Ǳ��ʱ��ȡ10%������
");
		set("value", 100);
   }
}

void init()
{
        object me = this_object();
        object who = this_player();
        object where = environment();
	if (wizardp(who))
		return;
        if (! me->query("my_owner") &&
             interactive (who))
        me->set("my_owner",who->query("id"));
       if (userp(where))
        {
         if (me->query("owned"))
           {
            if (me->query("owned")!=where->query("id"))
                  call_out("destruct_me",1,where,me);
           }
         else me->set("owned",where->query("id"));
       }
        add_action("do_deposit","carddeposit");
        add_action("do_withdraw","cardwithdraw");
        add_action("do_check", "cardbalance");
}
int do_deposit(string arg)
{
        string what, msg;
        int amount, new_amount;
        object what_ob, me;

        me = this_player();
        if( me->is_busy()||me->is_fight())
            return notify_fail("��������æ����...��\n");

        if(arg && sscanf(arg, "%d %s", amount, what)==2)
        {
			if (what == "gold-cash") {
				return notify_fail("��Ʊ����ֱ�Ӵ浽����\n");
			}
        if (what=="Ǳ��")
        {
        if (amount < 1||me->query("potential")-me->query("learned_points") < 1)
                  return notify_fail("��������Ǳ�ܣ�\n");
        if (amount>me->query("potential")-me->query("learned_points"))
                  return notify_fail("���Ǳ�ܲ����档\n");
        me->start_busy(1);
        msg = sprintf("$N�ó�%s��Ǳ�ܣ������"HIY"���ƽ�����"NOR"��\n",
                       chinese_number(amount));
        message_vision(msg, me);
        log_file("master_card", "[" + ctime(time())  + "]" + me->query("name") + "(" + me->query("id") + ") " + msg);
        new_amount = me->query("c_potential") + amount*9/10;
        if ( new_amount <= 0 )
        	return notify_fail("�㿨�е�Ǯ̫�൱�������\n");
        me->add("c_potential", amount*9/10);
        me->add("potential",-amount);
        me->save();
        return 1;
        }
        else what_ob = present(what + "_money", me);
        if (!what_ob)
             return notify_fail("������û�д�����Ǯ��\n");
        if (amount < 1)
             return notify_fail("��������" + what_ob->query("name") + "��\n");
        if ((int)what_ob->query_amount() < amount)
             return notify_fail("�����" + what_ob->query("name") + "������\n");
        me->start_busy(1);
        msg = sprintf("$N�ó�%s%s%s�������"HIY"���ƽ�����"NOR"��\n",
                chinese_number(amount), what_ob->query("base_unit"),
                what_ob->query("name"));
        message_vision(msg, me);
        log_file("master_card", "[" + ctime(time())  + "]" + me->query("name") + "(" + me->query("id") + ") " + msg);
        me->add("c_balance", what_ob->query("base_value") * amount);
        if ((int)what_ob->query_amount() == amount)
            destruct(what_ob);
        else
            what_ob->add_amount(-amount);
        me->save();
        return 1;
        }
        else return help(me);
}

int do_check()
{
   int total = (int)this_player()->query("c_balance");

   if(!total || total < 0)  {
        this_player()->set("c_balance", 0);
        write("�����ſ����Ѿ�ûǮ�ˡ�\n");
   }
   else write("������Ŀǰ����" + money_str(total) + "��\n");
   total = (int)this_player()->query("c_potential");
   if(!total || total < 0)  {
        this_player()->set("c_potential", 0);
        return notify_fail("�����ſ���û���κ�Ǳ����\n");
   }
   write("������Ŀǰ����" + chinese_number(total)+ "��Ǳ����\n");
   return 1;
}

int do_withdraw(string arg)
{
        int amount, v, rv;
        string what;
        object me;

        me = this_player();
        if( me->is_busy()||me->is_fight())
            return notify_fail("��������æ����...��\n");

        if (arg && sscanf(arg, "%d %s", amount, what) == 2)
        {
						if (what == "gold-cash") {
							return notify_fail("���ܴӿ���ȡ��Ʊ!\n");
						}

        if (amount < 1)
                   return notify_fail("����ȡ���٣�\n");
        if(what=="Ǳ��")
        {
        if (amount > me->query("c_potential"))
                     return notify_fail("�㿨���Ǳ�ܲ���ȡ��\n");
        me->start_busy(1);
        me->add("c_potential",-amount);
        me->add("potential",amount);
        me->save();
        message_vision(sprintf("$N��"HIY"���ƽ�����"NOR"��ȡ��%s��Ǳ�ܡ�\n",
                      chinese_number(amount)),me);
        return 1;
        }
        else if (file_size("/obj/money/" + what + ".c") < 0)
                   return notify_fail("����ȡ��ʲôǮ��\n");
        what = "/obj/money/" + what;
        if ((v = amount * what->query("base_value")) > me->query("c_balance"))
                   return notify_fail("�㿨���Ǯ����ȡ��\n");
        if( v < what->query("base_value") )
                   return notify_fail("��Ҫ����������Ȼ��������\n");
        me->start_busy(1);
        rv = v;
        v=v-pay_player(me, rv);
        me->add("c_balance",  -v);
        me->save();
        message_vision(sprintf("$N��"HIY"���ƽ�����"NOR"��ȡ��%s��\n", money_str(v)),
                me);
        return 1;
        }
        else return help(me);
}

string money_str(int amount)
{
       string output;
        if (amount / 10000) {
                output = chinese_number(amount / 10000) + "���ƽ�";
                amount %= 10000;
        }
        else
                output = "";
        if (amount / 100) {
                output = output + chinese_number(amount / 100) + "������";
                amount %= 100;
        }
        if (amount || sizeof(output)<2)
                return output + chinese_number(amount) + "��ͭ��";
        return output;
}
int pay_player(object who, int amount)
{
        int v;
        object ob;

        seteuid(getuid());
        if (amount < 1)
                amount = 0;
        if (v = amount / 10000) {
                ob = new("/obj/money/gold");
                ob->set_amount(amount / 10000);
                if(!(ob->move(who)))
                    return amount;
                amount %= 10000;
        }
        if (amount / 100) {
                ob = new("/obj/money/silver");
                ob->set_amount(amount / 100);
                if(!(ob->move(who)))
                    return amount;
                amount %= 100;
        }
        if (amount) {
                ob = new("/obj/money/coin");
                ob->set_amount(amount);
                if(!(ob->move(who)))
                    return amount;
        }
        return 0;
}
int help(object me)
{
write(@HELP

ȡǮ��  �����ʽ��cardwithdraw <����> <���ҵ�λ>
ȡǱ�ܣ������ʽ��cardwithdraw <����> Ǳ��
��Ǯ��  �����ʽ��carddeposit  <����> <���ҵ�λ>
��Ǳ�ܣ������ʽ��carddeposit  <����> Ǳ��
��ѯ�������ʽ��cardbalance
HELP
    );
    return 1;
}

void destruct_me(object where, object me)
{
  message_vision("ǧ��ֹ�����������$n���ž��ܣ���׷��\n",where,me);
  destruct (me);
}
int query_autoload() { return 1; }
