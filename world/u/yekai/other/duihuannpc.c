//wzx ȡ��NPC 2009.10.20

#include <ansi.h>
inherit NPC;
string huanqu();

void create()
{
        set_name(HIM"�u�u"NOR, ({"xuan xuan","xuan"}));
        set("gender", "Ů��" );
        set("age", 20);
        set("title",HIY"���ػ�����"NOR);
        set("long", HIG"\n\n������Ĺ��ػ�����\n\n"NOR);
        set("combat_exp", 1000000000);
        set("daoxing", 5000);
        set("attitude", "peaceful");
        set("per", 40);
        set("max_kee", 20000);
        set("max_gin", 20000);
        set("max_sen", 20000);
        set("inquiry", ([
                "��ȡ�澭" : (: huanqu :),
                ]) );
        setup();
        carry_object("/d/ourhome/obj/pink_cloth")->wear();
        carry_object("/d/ourhome/obj/shoes")->wear();
}

void init()
{
        add_action("do_agree", "agree");
}

string huanqu()
{
        object me=this_player();

      if ((int)me->query("combat_exp") > 10000000 ) //�������������
{
                command("say �ҿ��԰������ȡ���ʹ����칬����������Ҫ��˼��˼�°ɡ�");
                command("say ����кܶ�������ϲ�������ˣ����������һЩô��");
                return ("��Ը���(agree)��");
        }

        return ("�����ڵ��ǵ���У��һ��Ʋ������أ���ȥ���������ɡ�\n");
}

int do_agree(string arg)
{
        object who;
        who=this_player();
        seteuid(getuid());
        
        {
                    who->add("combat_exp",-5000000);  //�������������
                    who->add("daoxing",-5000000);  //�������������
                who->set("startroom","/d/city/kezhan");
       //ȡ��
       who->set("obstacle/yz","done");
	who->set("obstacle/jilei","done");
	who->set("obstacle/nuerguo","done");
	who->set("obstacle/firemount","done");
	who->set("obstacle/yuhua","done");
	who->set("obstacle/hf","done");
	who->set("obstacle/jindou","done");
	who->set("obstacle/yj","done");
	who->set("obstacle/fengxian","done");
	who->set("obstacle/tongtian","done");
	who->set("obstacle/sc","done");
	who->set("obstacle/yinwu","done");
	who->set("obstacle/jz","done");
	who->set("obstacle/chechi","done");
	who->set("obstacle/qinfa","done");
	who->set("obstacle/huoyun","done");
	who->set("obstacle/wudidong","done");
	who->set("obstacle/wuji","done");
	who->set("obstacle/liuer-mihou","done");
	who->set("obstacle/pingding","done");
	who->set("obstacle/biqiu","done");
	who->set("obstacle/baoxiang","done");
	who->set("obstacle/pansi","done");
	who->set("obstacle/baigudong","done");
	who->set("obstacle/zhuzi","done");
	who->set("obstacle/shushan","done");
	who->set("obstacle/wuzhuang","done");
	who->set("obstacle/xiaoxitian","done");
	who->set("obstacle/shenglingzhu","done");
	//who->set("obstacle/village","done");
	who->set("obstacle/niulang","done");
	who->set("obstacle/jingjiling","done");
	//who->set("obstacle/liusha","done");
	who->set("obstacle/tianzhu","done");
	//who->set("obstacle/huangfeng","done");
	who->set("obstacle/jisaiguo","done");
	who->set("obstacle/dudi","done");
	who->set("obstacle/jinping","done");
          who->set("obstacle/gao","done");
       who->set("obstacle/number",26);

       //������
       //who->set("9sky/number",9);
      //dntg
	  who->set("dntg/huaguo","done");
	  who->set("dntg/donghai","done");
	  who->set("dntg/hell","done");
	  who->set("dntg/bmw","done");
	  who->set("dntg/lijing","done");
	  who->set("dntg/pantao","done");
	  who->set("dntg/yaochi","done");
	  who->set("dntg/laojun","done");
	  who->set("dntg/erlang","done");
	  who->set("dntg/bagualu","done");
      who->set("dntg/number",10);
      //ڤ��
     //who->set("mingjie/number",15);
      //12gong
     //who->set("12gong/number",12);
      

                command("say �ð�");
                command("chat  ��ϲ��"+who->query("name")+"�ù��ػ����˻�ȡ���澭��\n");
                command ("heihei");
                who->move("/d/city/kezhan");
                who->save();

                return 1;
        }
}



