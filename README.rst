.. _MktDrivenInst:

Market Driven Institution
=========================
This page describes the MktDrivenInst. This is a library generated for use
with the Cyclus simulator.

To use this library, first make sure that you have the dependencies installed,
namely |Cyclus|, CMake, and a recent version of Python (2.7 or 3.3+).

First, you need to get the ``MktDrivenInst`` code.
You can grab the MktDrivenInst by using git to
`clone the repository <https://github.com/katyhuff/MktDrivenInst.git>`_

**Getting MktDrivenInst via git:**

.. code-block:: bash

    $ git clone https://github.com/katyhuff/MktDrivenInst.git
    $ cd MktDrivenInst

------------

Now that we have the code, let's compile and install the ``MktDrivenInst`` project.  This
is done with the install.py script.
Where did you install Cyclus? If you used a ``$PREFIX`` for cyclus, use the same one here. I used ``../install``.

.. code-block:: bash

    tutorial $ python install.py --prefix=../install

------------

Let's run |cyclus| with the MktDrivenInst! In the input directory there is
an :file:`example.xml`. Running |cyclus| on this file with the command
``cyclus input/example.xml`` should produce the following output.

.. code-block:: bash

    tutorial $ cyclus input/example.xml
                  :
              .CL:CC CC             _Q     _Q  _Q_Q    _Q    _Q              _Q
            CC;CCCCCCCC:C;         /_\)   /_\)/_/\\)  /_\)  /_\)            /_\)
            CCCCCCCCCCCCCl       __O|/O___O|/O_OO|/O__O|/O__O|/O____________O|/O__
         CCCCCCf     iCCCLCC     /////////////////////////////////////////////////
         iCCCt  ;;;;;.  CCCC
        CCCC  ;;;;;;;;;. CClL.                          c
       CCCC ,;;       ;;: CCCC  ;                   : CCCCi
        CCC ;;         ;;  CC   ;;:                CCC`   `C;
      lCCC ;;              CCCC  ;;;:             :CC .;;. C;   ;    :   ;  :;;
      CCCC ;.              CCCC    ;;;,           CC ;    ; Ci  ;    :   ;  :  ;
       iCC :;               CC       ;;;,        ;C ;       CC  ;    :   ; .
      CCCi ;;               CCC        ;;;.      .C ;       tf  ;    :   ;  ;.
      CCC  ;;               CCC          ;;;;;;; fC :       lC  ;    :   ;    ;:
       iCf ;;               CC         :;;:      tC ;       CC  ;    :   ;     ;
      fCCC :;              LCCf      ;;;:         LC :.  ,: C   ;    ;   ; ;   ;
      CCCC  ;;             CCCC    ;;;:           CCi `;;` CC.  ;;;; :;.;.  ; ,;
        CCl ;;             CC    ;;;;              CCC    CCL
       tCCC  ;;        ;; CCCL  ;;;                  tCCCCC.
        CCCC  ;;     :;; CCCCf  ;                     ,L
         lCCC   ;;;;;;  CCCL
         CCCCCC  :;;  fCCCCC
          . CCCC     CCCC .
           .CCCCCCCCCCCCCi
              iCCCCCLCf
               .  C. ,
                  :

    <details>
    Status: Cyclus run successful!
    Output location: cyclus.sqlite
    Simulation ID: 0ae730e0-a9a8-4576-afaa-d1db6399d5a2
