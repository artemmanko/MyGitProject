%define _unpackaged_files_terminate_build 1

Name:    HelloUniverse
Version: 2.0
Release: alt2
Summary: Most simple RPM package
License: GPL-1.0
Group:   Development/Other
Source:  %name-%version.tar
Patch:   %name-%version-%release.patch
BuildRequires: gcc-c++

%description
This is my first RPM

%prep
%setup
%autopatch -p1

%build
%make_build HelloUniverse

%install
mkdir -p %{buildroot}%_bindir
install -m 755 HelloUniverse %{buildroot}%_bindir

%files
%_bindir/%name

%changelog
* Wed May 01 2024 Some One <someone@altlinux.org> 2.0-alt2
- Instructions for build by release tag added.

* Wed May 01 2024 Some One <someone@altlinux.org> 2.0-alt1
- New source fiture added.

* Mon Apr 01 2024 Some One <someone@altlinux.org> 1.0-alt1
- Init Build

