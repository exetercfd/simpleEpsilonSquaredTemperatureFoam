    fvScalarMatrix TEqn
    (
          fvm::div(phi,T)
        ==
          fvm::laplacian((kfe+kse)/(rhof*cpf*eps),T,"laplacian(DT,T)")
    );
    TEqn.relax();
    TEqn.solve();