// by lxmas 19/10/2005

#include <ansi.h>
inherit NPC;

void create()
{
  set_name("���", ({"xiao adina", "adina"}));
  set("long", @LONG
�����Ǵ�˵�еĴ���Ǳ�ܼ�������ˣ�Ҳ�Ǻ������ĺ����ţ������ᡣ

��ѯǱ�ܵĻ�����������ָ���:
jisuan AtoBforC ����jisuan A B C

A ָ���Ŀǰskill����...ȡֵ0-3000
B ָ���Ŀ��skill����...ȡֵA-3000
C ָ�������...ȡֵ10-999
LONG);

       set("gender", "Ů��");
       set("age", 20);
       set("int", 25+random(5));
       set("title", HIR "Ǳ�ܼ��������" NOR);
       set("attitude", "peaceful");
       set("combat_exp", 350000);
       set("daoxing", 10000000);
       set("rank_info/respect", "��������");
       set("class","dragon");
       set("per", 30);
       set("max_kee", 1000);
       set("max_sen", 1000);
       set("force", 3000);
       set("max_force", 3000);
       set("force_factor", 100);
       set("max_mana", 3000);
       set("mana", 3000);
       set("mana_factor", 100);
       set_skill("literate", 500);
       set_skill("unarmed", 500);
       set_skill("dodge", 500);
       set_skill("force", 500);
       set_skill("parry", 500);
       set_skill("fork", 500);
       set_skill("spells", 500);
       set_skill("seashentong", 500);
       set_skill("dragonfight", 500);
       set_skill("dragonforce", 500);
       set_skill("fengbo-cha", 500);
       set_skill("dragonstep", 500);
       map_skill("spells", "seashentong");
       map_skill("unarmed", "dragonfight");
       map_skill("force", "dragonforce");
       map_skill("fork", "fengbo-cha");
       map_skill("parry", "fengbo-cha");
       map_skill("dodge", "dragonstep");
       set("inquiry", ([
                "name": "�Ҿ��Ƿ����ᰡ���������Ǳ���ˡ�",
                "����": "�Ҿ��Ƿ����ᰡ���������Ǳ���ˡ�",
                "����": "�Ҿ��Ƿ����ᰡ���������Ǳ���ˡ�",
                "Ǳ��": "��ѯǱ�ܵĻ�������:jisuan AtoBforC ����jisuan A B C��",
                "����": "���������Ϲ�������׼�۸����ϣ����Ϲ��������ˡ�",
                "������": "���������Ϲ�������׼�۸����ϣ����Ϲ��������ˡ�",
                "lxmas": "���������Ϲ�������׼�۸����ϣ����Ϲ��������ˡ�",
        ]));


       create_family("��������", 2, "ˮ��");
	setup();

       carry_object("/d/obj/cloth/pinkskirt")->wear();
       carry_object("/d/sea/obj/yincha")->wield();

        remove_call_out ("says");
	call_out("says",3);
}

void says ()
{
  string *msgs = ({
    "$N΢Ц�ؿ����㣬��λС����������Ǳ�ܵ���\n",
    "Ҫ��Ǳ�ܵĻ���look ��һ�¾�����ˡ�$N����һ��������\n",
    "��ô���㲻��Ǳ�ܰ���$N��Щ��������...\n",
    "����Ǳ�ܾ��뿪�ɣ�����ϲ���徻�ġ�\n",
    "$N������գ��ҵĺ����������أ�\n",
  });
  message_vision (msgs[random(sizeof(msgs))],this_object());
  remove_call_out ("says");
  call_out("says",random(120));
}

void init()
{
add_action("do_jisuan","jisuan");
}

int do_jisuan( string arg )
{
  object me = this_object();
  object who = this_player();
  int sk1,sk2,wx;
  float qn1,qn2,wx2,dh;

  if(this_player()->is_busy())
      return notify_fail("����æ���أ�����\n");

  if(!arg) return notify_fail("С���ѣ����ǲ��Ǹ�ʽ������˰���\n");

  if( sscanf( arg, "%dto%dfor%d", sk1, sk2, wx )==3
	|| sscanf( arg, "%d %d %d", sk1, sk2, wx )==3 );
	else return notify_fail("С���ѣ����ǲ��Ǹ�ʽ������˰���\n");

  if (wx<10&&wx>=0)
  		write("��˵"+who->name()+"�����"+wx+"������Ҳ�ҳ����죿�������ײ�����ˣ�\n");
  else if (wx>999)
    	write("�ڿ�����ҿ쿴��"+who->name()+"������û�зⶥ�������bug�����ҷ����������ˣ�\n");
  else if (sk1<0||sk1>3000)
     write("��ʦע���ˣ�"+who->name()+"���书�����⣬��������bug������֪ͨlxmas���ȴ������ն�ɣ�\n");
  else if (sk2<0||sk2>3000)
     write("��ʦע���ˣ�"+who->name()+"���书�����⣬��������bug������֪ͨlxmas���ȴ������ն�ɣ�\n");
  else if (sk1>sk2)
     write("������"+who->name()+"�Ѿ����ķ��ϻ�ͯ�ˣ�\n");
  else if (sk1==sk2)
	 write("ˣ�Ұ�������㲻���Լ��㣿���㻹��"+wx+"�����ԣ��״��ˣ�\n");
  else if (sk1>=0&&sk1<=3000&&sk2>sk1&&sk2<=3000&&wx>9&&wx<=999) {
       if (sk1==0)
          qn1=1.0*sk2*(sk2+1)*(2*sk2+1)/(3*wx);
        else
          qn1=1.0*sk2*(sk2+1)*(2*sk2+1)/(3*wx)-sk1*(sk1+1)*(2*sk1+1)/(3*wx);
        qn2=1.0*4*qn1;
        wx2=1.0*(sk2-1)*(sk2-1)*(sk2-1)/10;
        dh=1.0*wx2/1000;
        write("���¿���"+who->name()+"? \n����"+sk1+"������"+sk2+"������ҪǱ��"+qn1+"�㣬�ı��д���ҪǱ��"+qn2+"�㡣\n");
        write("ͬʱ������Ҫ��"+wx2+"����ѧ֧�֣�����ѧϰ��Ҫ"+dh+"�����֧�֡�\n");
  }
  else write("С���ѣ����ǲ��Ǹ�ʽ������˰���\n");
  return 1;
}