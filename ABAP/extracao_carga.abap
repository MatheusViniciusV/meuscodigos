*&---------------------------------------------------------------------*
*& Report ZDGP2_EXTRACAO_CARGA
*&---------------------------------------------------------------------*
REPORT zdgp2_extracao_carga.

*---------------------------------------------------------------------*
* CONSTANTS
*---------------------------------------------------------------------*
CONSTANTS:
  gc_filename_extracao TYPE string VALUE '\DGP2_Extracao.csv',
  gc_sep               TYPE c VALUE ';',
  gc_filetype_csv      TYPE c LENGTH 10 VALUE 'ASC',
  gc_header_mat        TYPE string VALUE 'MATERIAL',
  gc_header_stat       TYPE string VALUE 'STATUS DE PROCESSAMENTO',
  gc_log_obj           TYPE balobj_d VALUE 'ZDGP2_EX_CAR',
  gc_log_sub           TYPE balsubobj VALUE 'PROCESSO'.

*---------------------------------------------------------------------*
* TYPES
*---------------------------------------------------------------------*
TYPES:
  BEGIN OF ty_s_material_csv,
    material   TYPE string,
    procstatus TYPE string,
  END OF ty_s_material_csv,
  ty_t_material_csv TYPE TABLE OF ty_s_material_csv,

  BEGIN OF ty_s_bdcdata,
    program  TYPE bdcdata-program,
    dynpro   TYPE bdcdata-dynpro,
    dynbegin TYPE bdcdata-dynbegin,
    fnam     TYPE bdcdata-fnam,
    fval     TYPE bdcdata-fval,
  END OF ty_s_bdcdata,
  ty_t_bdcdata TYPE TABLE OF ty_s_bdcdata,

  BEGIN OF ty_s_alv,
    icon       TYPE icon_d,
    material   TYPE string,
    procstatus TYPE string,
    message    TYPE string,
    status     TYPE char1,
  END OF ty_s_alv,
  ty_t_alv TYPE TABLE OF ty_s_alv.

*---------------------------------------------------------------------*
* DATA
*---------------------------------------------------------------------*
DATA:
  gt_file_table        TYPE filetable,
  gs_file_table        TYPE file_table,
  gv_rc                TYPE i,
  gt_material_tab      TYPE TABLE OF bapi1078_matsel,
  gt_return            TYPE TABLE OF bapiret2,
  gt_matperigosos      TYPE TABLE OF bapi1078_dangerousgooddata,
  gs_matperigoso       TYPE bapi1078_dangerousgooddata,
  gt_csv_output        TYPE ty_t_material_csv,
  gs_csv_output        TYPE ty_s_material_csv,
  gt_csv_raw_data      TYPE TABLE OF string,
  gt_csv_struc_data    TYPE ty_t_material_csv,
  gt_material_csv_text TYPE truxs_t_text_data,
  gv_full_path         TYPE string,
  gt_bdcdata           TYPE ty_t_bdcdata,
  gt_messages          TYPE TABLE OF bdcmsgcoll,
  gv_message           TYPE string,
  gt_alv               TYPE ty_t_alv,
  gv_log_handle        TYPE balloghndl,
  gs_log_header        TYPE bal_s_log,
  gs_log_msg           TYPE bal_s_msg,
  gv_aux               TYPE string.

*---------------------------------------------------------------------*
* SELECTION-SCREEN
*---------------------------------------------------------------------*
SELECTION-SCREEN BEGIN OF BLOCK b1 WITH FRAME TITLE TEXT-001.
  PARAMETERS: rbextrac RADIOBUTTON GROUP g1 DEFAULT 'X',
              rbcarg   RADIOBUTTON GROUP g1.
SELECTION-SCREEN END OF BLOCK b1.

SELECTION-SCREEN BEGIN OF BLOCK b2 WITH FRAME TITLE TEXT-002.
  PARAMETERS: p_lpath TYPE string OBLIGATORY.
SELECTION-SCREEN END OF BLOCK b2.

*---------------------------------------------------------------------*
* AT SELECTION-SCREEN
*---------------------------------------------------------------------*
AT SELECTION-SCREEN ON VALUE-REQUEST FOR p_lpath.

  DATA: lt_dynpfields TYPE STANDARD TABLE OF dynpread.

  lt_dynpfields = VALUE #(
    ( fieldname = 'RBEXTRAC' )
    ( fieldname = 'RBCARG' )
  ).

  CALL FUNCTION 'DYNP_VALUES_READ'
    EXPORTING
      dyname     = sy-cprog
      dynumb     = sy-dynnr
    TABLES
      dynpfields = lt_dynpfields.
  IF sy-subrc <> 0.
*   MESSAGE ID SY-MSGID TYPE SY-MSGTY NUMBER SY-MSGNO
*     WITH SY-MSGV1 SY-MSGV2 SY-MSGV3 SY-MSGV4.
  ENDIF.

  LOOP AT lt_dynpfields ASSIGNING FIELD-SYMBOL(<ls_dynpfields>).

    IF <ls_dynpfields>-fieldname = 'RBEXTRAC'.
      rbextrac = <ls_dynpfields>-fieldvalue.
    ELSEIF <ls_dynpfields>-fieldname = 'RBCARG'.
      rbcarg = <ls_dynpfields>-fieldvalue.
    ENDIF.

  ENDLOOP.

  " Se extração, pede uma PASTA. Se carga, pede um ARQUIVO.
  IF rbextrac = abap_true.
    CALL METHOD cl_gui_frontend_services=>directory_browse
      CHANGING
        selected_folder = p_lpath
      EXCEPTIONS
        cntl_error      = 1
        OTHERS          = 2.
    IF sy-subrc <> 0.
      MESSAGE 'Erro ao selecionar diretório.' TYPE 'E'.
    ENDIF.

  ELSEIF rbcarg = abap_true.
    CALL METHOD cl_gui_frontend_services=>file_open_dialog
      EXPORTING
        default_filename = '*.CSV'
      CHANGING
        file_table       = gt_file_table
        rc               = gv_rc
      EXCEPTIONS
        OTHERS           = 1.

    IF sy-subrc = 0 AND gv_rc = 1.
      READ TABLE gt_file_table INTO gs_file_table INDEX 1.
      IF sy-subrc = 0.
        p_lpath = gs_file_table-filename.
      ENDIF.
    ENDIF.
  ENDIF.

*---------------------------------------------------------------------*
* START-OF-SELECTION
*---------------------------------------------------------------------*
START-OF-SELECTION.

  IF rbextrac = abap_true.
    PERFORM iniciar_log USING 'EXTRACAO'.
    PERFORM extrair_dados.
    PERFORM registrar_log USING 'S' 'Execução de extração finalizada.'.
    PERFORM salvar_log.
  ELSEIF rbcarg = abap_true.
    PERFORM iniciar_log USING 'CARGA'.
    PERFORM carregar_dados.
    PERFORM registrar_log USING 'S' 'Execução de carga finalizada.'.
    PERFORM salvar_log.
  ENDIF.

*---------------------------------------------------------------------*
* FORM extrair_dados
*---------------------------------------------------------------------*
FORM extrair_dados.
  PERFORM selecionar_materiais.
  PERFORM obter_dados_perigosos.
  PERFORM gerar_csv_output.
  PERFORM salvar_csv_arquivo.
ENDFORM.

*---------------------------------------------------------------------*
* FORM selecionar_materiais
*---------------------------------------------------------------------*
FORM selecionar_materiais.
  SELECT matnr AS material FROM mara INTO TABLE gt_material_tab.
  IF gt_material_tab IS INITIAL.
    PERFORM registrar_log USING 'E' 'Nenhum material encontrado na MARA.'.
    MESSAGE 'Nenhum material encontrado na MARA.' TYPE 'E'.
  ELSE.
    gv_aux = |{ lines( gt_material_tab ) } materiais lidos da MARA|.
    PERFORM registrar_log USING 'S' gv_aux.
  ENDIF.
ENDFORM.

*---------------------------------------------------------------------*
* FORM obter_dados_perigosos
*---------------------------------------------------------------------*
FORM obter_dados_perigosos.
  CALL FUNCTION 'BAPI_DANGEROUSGOOD_GETDETAIL'
    TABLES
      return            = gt_return
      material_tab      = gt_material_tab
      dangerousgooddata = gt_matperigosos.

  LOOP AT gt_return INTO DATA(ls_return) WHERE type = 'E' OR type = 'A'.
    gv_aux = |{ ls_return-message }|.
    PERFORM registrar_log USING 'E' gv_aux.
    MESSAGE ls_return-message TYPE 'E'.
  ENDLOOP.

  gv_aux = |{ lines( gt_matperigosos ) } registros retornados pela BAPI|.
  PERFORM registrar_log USING 'S' gv_aux.
ENDFORM.

*---------------------------------------------------------------------*
* FORM gerar_csv_output
*---------------------------------------------------------------------*
FORM gerar_csv_output.
  CLEAR gs_csv_output.
  gs_csv_output-material   = gc_header_mat.
  gs_csv_output-procstatus = gc_header_stat.
  APPEND gs_csv_output TO gt_csv_output.

  LOOP AT gt_matperigosos INTO gs_matperigoso.
    APPEND VALUE #( material = gs_matperigoso-material
                    procstatus = gs_matperigoso-procstatus ) TO gt_csv_output.
  ENDLOOP.

  IF lines( gt_csv_output ) <= 1.
    PERFORM registrar_log USING 'I' 'Nenhum dado retornado pela BAPI.'.
    MESSAGE 'Nenhum dado de produto perigoso retornado pela BAPI.' TYPE 'I'.
  ELSE.
    gv_aux = |{ lines( gt_csv_output ) - 1 } linhas adicionadas ao CSV.|.
    PERFORM registrar_log USING 'S' gv_aux.
  ENDIF.
ENDFORM.

*---------------------------------------------------------------------*
* FORM salvar_csv_arquivo
*---------------------------------------------------------------------*
FORM salvar_csv_arquivo.
  CALL FUNCTION 'SAP_CONVERT_TO_CSV_FORMAT'
    EXPORTING
      i_field_seperator    = gc_sep
    TABLES
      i_tab_sap_data       = gt_csv_output
    CHANGING
      i_tab_converted_data = gt_material_csv_text.

  CONCATENATE p_lpath gc_filename_extracao INTO gv_full_path.

  CALL FUNCTION 'GUI_DOWNLOAD'
    EXPORTING
      filename              = gv_full_path
      filetype              = gc_filetype_csv
      write_field_separator = 'X'
    TABLES
      data_tab              = gt_material_csv_text.

  IF sy-subrc = 0.
    gv_aux = |Arquivo salvo em: { gv_full_path }|.
    PERFORM registrar_log USING 'S' gv_aux.
  ELSE.
    PERFORM registrar_log USING 'E' 'Erro ao salvar arquivo CSV.'.
  ENDIF.
ENDFORM.

*---------------------------------------------------------------------*
* FORM carregar_dados
*---------------------------------------------------------------------*
FORM carregar_dados.
  PERFORM upload_csv_entrada.
  PERFORM processar_csv.
  PERFORM executar_bdc_em_lote.
  PERFORM exibir_alv_resultados.
ENDFORM.

*---------------------------------------------------------------------*
* FORM upload_csv_entrada
*---------------------------------------------------------------------*
FORM upload_csv_entrada.
  CALL METHOD cl_gui_frontend_services=>gui_upload
    EXPORTING
      filename = p_lpath
      filetype = gc_filetype_csv
    CHANGING
      data_tab = gt_csv_raw_data.

  IF sy-subrc <> 0.
    PERFORM registrar_log USING 'E' 'Erro ao ler o arquivo CSV de entrada.'.
    MESSAGE 'Erro ao ler o arquivo.' TYPE 'E'.
  ELSE.
    gv_aux = |Arquivo lido: { p_lpath }|.
    PERFORM registrar_log USING 'S' gv_aux.
  ENDIF.
ENDFORM.

*---------------------------------------------------------------------*
* FORM processar_csv
*---------------------------------------------------------------------*
FORM processar_csv.
  DATA(ls_line) = VALUE ty_s_material_csv( ).
  LOOP AT gt_csv_raw_data INTO DATA(wa_string) FROM 2.
    SPLIT wa_string AT gc_sep INTO ls_line-material ls_line-procstatus.
    APPEND ls_line TO gt_csv_struc_data.
  ENDLOOP.

  gv_aux = |{ lines( gt_csv_struc_data ) } linhas processadas do CSV.|.
  PERFORM registrar_log USING 'S' gv_aux.
ENDFORM.

*---------------------------------------------------------------------*
* FORM executar_bdc_em_lote
*---------------------------------------------------------------------*
FORM executar_bdc_em_lote.
  LOOP AT gt_csv_struc_data INTO DATA(wa_line).
    PERFORM montar_bdc USING wa_line.
    PERFORM executar_transacao USING wa_line.
  ENDLOOP.
ENDFORM.

*---------------------------------------------------------------------*
* FORM montar_bdc
*---------------------------------------------------------------------*
FORM montar_bdc USING ps_line TYPE ty_s_material_csv.
  CLEAR gt_bdcdata.

  APPEND INITIAL LINE TO gt_bdcdata ASSIGNING FIELD-SYMBOL(<gs_bdcdata>).
  <gs_bdcdata>-program = 'SAPLDG01'.
  <gs_bdcdata>-dynpro = '1010'.
  <gs_bdcdata>-dynbegin = 'X'.

  APPEND VALUE #( fnam = 'BDC_CURSOR' fval = 'RDGMDSEL-MATNR' ) TO gt_bdcdata.
  APPEND VALUE #( fnam = 'BDC_OKCODE' fval = '=GRSL' ) TO gt_bdcdata.
  SHIFT ps_line-material LEFT DELETING LEADING '0'. " Retira zeros à esquerda
  APPEND VALUE #( fnam = 'RDGMDSEL-MATNR' fval = ps_line-material ) TO gt_bdcdata.
  APPEND VALUE #( fnam = 'RDGMDSEL-VALDAT' fval = |{ sy-datum+6(2) }.{ sy-datum+4(2) }.{ sy-datum(4) }| ) TO gt_bdcdata.

  APPEND VALUE #( program = 'SAPLCBDU_DL00' dynpro = '1100' dynbegin = 'X' ) TO gt_bdcdata.
  APPEND VALUE #( fnam = 'BDC_OKCODE' fval = '=OSAV' ) TO gt_bdcdata.
  APPEND VALUE #( fnam = 'RDGMDIOT-DGWOS(01)' fval = ps_line-procstatus ) TO gt_bdcdata.
ENDFORM.

*---------------------------------------------------------------------*
* FORM executar_transacao
*---------------------------------------------------------------------*
FORM executar_transacao USING ps_line TYPE ty_s_material_csv.
  CALL TRANSACTION 'DGP2' USING gt_bdcdata
    MODE 'N' UPDATE 'S'
    MESSAGES INTO gt_messages.

  READ TABLE gt_messages INTO DATA(lv_line_message) INDEX lines( gt_messages ).

  DATA lv_msg TYPE string.
  CALL FUNCTION 'FORMAT_MESSAGE'
    EXPORTING
      id   = lv_line_message-msgid
      lang = lv_line_message-msgspra
      no   = lv_line_message-msgnr
      v1   = lv_line_message-msgv1
      v2   = lv_line_message-msgv2
      v3   = lv_line_message-msgv3
      v4   = lv_line_message-msgv4
    IMPORTING
      msg  = lv_msg.

  DATA lv_icon TYPE icon_d.

  CASE lv_line_message-msgtyp.
    WHEN 'S'.
      lv_icon = icon_led_green.
      gv_aux = |Material { ps_line-material } atualizado com sucesso.|.
      PERFORM registrar_log USING 'S' gv_aux.
    WHEN 'I'.
      lv_icon = icon_led_yellow.
      gv_aux = |Material { ps_line-material } sem alteração.|.
      PERFORM registrar_log USING 'I' gv_aux.
    WHEN OTHERS.
      lv_icon = icon_led_red.
      gv_aux = |Material { ps_line-material } erro: { lv_msg }|.
      PERFORM registrar_log USING 'E' gv_aux.
  ENDCASE.

  APPEND VALUE #( icon       = lv_icon
                  material   = ps_line-material
                  procstatus = ps_line-procstatus
                  message    = lv_msg
                  status     = lv_line_message-msgtyp ) TO gt_alv.
ENDFORM.

*---------------------------------------------------------------------*
* FORM exibir_alv_resultados
*---------------------------------------------------------------------*
FORM exibir_alv_resultados.
  TRY.
      cl_salv_table=>factory(
        IMPORTING r_salv_table = DATA(lo_alv)
        CHANGING  t_table      = gt_alv ).
      lo_alv->display( ).
    CATCH cx_salv_error INTO DATA(lo_error).
      MESSAGE lo_error->get_text( ) TYPE 'E'.
  ENDTRY.
ENDFORM.

*---------------------------------------------------------------------*
* FORM iniciar_log
*---------------------------------------------------------------------*
FORM iniciar_log USING pv_action TYPE string.
  DATA(lv_timestamp) = |{ sy-datum }_{ sy-uzeit }|.
  TRANSLATE lv_timestamp USING '_:'.
  gs_log_header-object    = gc_log_obj.
  gs_log_header-subobject = gc_log_sub.
  gs_log_header-extnumber = |{ pv_action }_{ lv_timestamp }|.
  gs_log_header-aluser    = sy-uname.
  gs_log_header-alprog    = sy-repid.
  gs_log_header-aldate    = sy-datum.
  gs_log_header-altime    = sy-uzeit.

  CALL FUNCTION 'BAL_LOG_CREATE'
    EXPORTING
      i_s_log      = gs_log_header
    IMPORTING
      e_log_handle = gv_log_handle.

  gv_aux = |Início da execução: { pv_action }|.
  PERFORM registrar_log USING 'S' gv_aux.
ENDFORM.

*---------------------------------------------------------------------*
* FORM registrar_log
*---------------------------------------------------------------------*
FORM registrar_log USING pv_type TYPE symsgty
                         pv_text TYPE string.
  CLEAR gs_log_msg.
  gs_log_msg-msgty = pv_type.
  gs_log_msg-msgid = 'Z1'.
  gs_log_msg-msgno = '000'.
  gs_log_msg-msgv1 = pv_text.

  CALL FUNCTION 'BAL_LOG_MSG_ADD'
    EXPORTING
      i_log_handle = gv_log_handle
      i_s_msg      = gs_log_msg.
ENDFORM.

*---------------------------------------------------------------------*
* FORM salvar_log
*---------------------------------------------------------------------*
FORM salvar_log.
  DATA lt_handle TYPE bal_t_logh.

  APPEND gv_log_handle TO lt_handle.

  CALL FUNCTION 'BAL_DB_SAVE'
    EXPORTING
      i_t_log_handle = lt_handle
    EXCEPTIONS
      OTHERS         = 1.

  CALL FUNCTION 'BAL_LOG_REFRESH'
    EXPORTING
      i_log_handle = gv_log_handle
    EXCEPTIONS
      OTHERS       = 1.
ENDFORM.
