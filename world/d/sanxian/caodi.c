// edited by mind
inherit ROOM;
void create()
{
  set("short","�µײݵ�");
  set("long",@LONG
�ǳ��������Ĳݵأ��������ݣ������ͺ������ű��̵�̺�ӡ�
�����Ĺ����У������˷ҷ�������������֦Ҷï�ܵ����֡���ľ��
����׺��һЩ���޵Ļ��ݣ�����Ҫ��Ϊ�Լ�ͻȻ�������ɾ����
�ɾ�Ψһ���µģ��������ޱߵľ��ţ�û�з磬Ҳû��������ÿһ
���ݣ�ÿһƬҶ�ӣ����Ǿ��Ծ�ֹ�ģ�������������û��˿��������
����µľ��ţ���ֱҪ���˷���
�������ġ��ɾ����������ǿ顰���ء���
LONG
  );
   set("objects", ([
      
   ]) );  
        set("no_magic",1);
        
        setup();
}

void init()
{
   add_action("do_search", "search");
   add_action("do_look", "look");
   add_action("feeling", "feel");
}

int do_look(string arg)
{
   object me;

   me = this_player();
   if (!arg || (arg != "����" && arg != "tree"))
      return 0;
   if(me->query_temp("mark/foundtree"))
      tell_object(me, "���������֡��ܴ�Ҷ���ر�Բ���°�ص���Ƥ��
�����ϰ�ز�ͬ���ϰ�ص���Ƥ�ֲڣ��°�ص���Ƥȴ
�⻬�úܡ���������������йŹ֣�����Ƥ���ǳ�����
���������ģ���ΪʲôҪ��(feel)����Ƥ����Ȼֻ��һ
�����ͣ������������������ض����ǵ��š���\n");
        me->set_temp("mark/foundbark", 1);
   return 1;
}

int do_search(string arg)
{
   object me;
   int llvl;

   me = this_player();
   llvl = (int)me->query("kar");
   if(me->query_temp("mark/foundtree"))tell_object(me, "�������ܵ������﷢��һ�ô���(tree)��\n");
   if (!arg) {
      if(random(100) < llvl) {
         tell_object(me, "�������ܵ������﷢��һ�ô���(tree)��\n");
         me->set_temp("mark/foundtree", 1);
         return 1;
      }
      if(!me->query_temp("mark/foundtree")){
      message_vision("$N�����ܵ����ֺͲݵ��ﲻͣ�ز��ң���ͷ�󺹡�\n", me);
      tell_object(me, "��û�з����κ�ֵ�����ʵ����\n");
      
      } 
   }
  return 1; 
   
}



int feeling(string arg)
{
        object obj;
        object me;
                
        if(!arg || arg=="")
        {
                write("��Ҫ����ʲô��\n");
                return 1;
        }
        if( arg == "��Ƥ" || arg == "bark" )
        {
        me = this_player();
        if(me->query_temp("mark/foundbark")){
        message_vision("$N���ڲݵ��ϣ���ϸ�����Ŵ������°����Ƥ��\n", me);
        me->start_busy(2);
        call_out("searching",2,me);
        me->stop_busy();
        message("vision","ֻ�������ꡱһ�����·�۶�ʲô���أ������ѿ�һ������"+me->name() + "�Ͻ����˽�ȥ��\n", environment(me),me);
        return 1;
        }
        }

        else
        {
                write("���ѵ��ܴ�"+arg+"��������������\n");
                return 1;
        }

}
int searching(object me)
{
        if( !me->is_ghost()) {
        me->move(__DIR__"shudong");
        message_vision("ֻ�������ꡱһ�����·�۶�ʲô���أ������ѿ�һ������$N�Ͻ����˽�ȥ��\n", me);
        }
        return 1;
}

